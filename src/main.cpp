//************************************************************
// this is a simple example that uses the painlessMesh library
//
// 1. sends a silly message to every node on the mesh at a random time between 1 and 5 seconds
// 2. prints anything it receives to Serial.print
// bootstrap a new device:
// pio run -t uploadfs
// pio run -t upload
//************************************************************
#include "painlessMesh.h"
#include <NeoPixelBus.h>
#include "main.h"
#include "FS.h"
#include "animationController.h"


#define   MESH_PREFIX      "whateverYouLike"
#define   MESH_PASSWORD    "somethingSneaky"
#define   MESH_PORT        5555
#define   COLOR_SATURATION 128
#define   CONFIG_FILE       "/config.json"

const uint16_t PixelCount = 50;

Scheduler userScheduler; // to control your personal task
painlessMesh  mesh;
AnimationController* animCtrl;

config_t config;         // Current configuration

// User stub
void sendMessage() ; // Prototype so PlatformIO doesn't complain

Task taskSendMessage( TASK_SECOND * 1 , TASK_FOREVER, &sendMessage );

void sendMessage() {
  String msg = "Hello from node ";
  msg += mesh.getNodeId();
  mesh.sendBroadcast( msg );
  taskSendMessage.setInterval( random( TASK_SECOND * 1, TASK_SECOND * 5 ));
}

// Needed for painless library
void receivedCallback( uint32_t from, String &msg ) {
  Serial.printf("startHere: Received from %u msg=%s\n", from, msg.c_str());
  //TODO: json deserialize this string, multiple message types?
}

void newConnectionCallback(uint32_t nodeId) {
    Serial.printf("--> startHere: New Connection, nodeId = %u\n", nodeId);
}

void changedConnectionCallback() {
    Serial.printf("Changed connections %s\n",mesh.subConnectionJson().c_str());
}

void nodeTimeAdjustedCallback(int32_t offset) {
    Serial.printf("Adjusted time %u. Offset = %d\n", mesh.getNodeTime(),offset);
}


/////////////////////////////////////////////////////////
//
//  JSON / Configuration Section
//
/////////////////////////////////////////////////////////

// Configuration Validations TODO
void validateConfig() {}

// De-Serialize Network config
void dsConfig(JsonObject &json) {
  // Generate default hostname if needed
  config.hostname = json["hostname"].as<String>();
  if (!config.hostname.length()) {
    char chipId[7] = {0};
    snprintf(chipId, sizeof(chipId), "%06x", ESP.getChipId());
    config.hostname = "fmesh-" + String(chipId);
  }

	// Fallback to embedded ssid and passphrase if null in config
	config.ssid = json["ssid"].as<String>();
	if (!config.ssid.length())
		config.ssid = "fireflyMesh";

	config.passphrase = json["passphrase"].as<String>();
	if (!config.passphrase.length())
		config.passphrase = "fireflyMesh";

  config.gamma = json["gamma"];
  config.pixelCount = json["pixelCount"];
}

// Load configugration JSON file
void loadConfig() {
	// Zeroize Config struct
	memset(&config, 0, sizeof(config));

	// Load CONFIG_FILE json. Create and init with defaults if not found
	File file = SPIFFS.open(CONFIG_FILE, "r");
	if (!file) {
		Serial.println(F("- No configuration file found."));
		config.ssid = "fireflyMesh";
		config.passphrase = "fireflyMesh";
		saveConfig();
	} else {
		// Parse CONFIG_FILE json
		size_t size = file.size();
		if (size > 2048) {
			Serial.println(F("*** Configuration File too large ***"));
			return;
		}

		std::unique_ptr<char[]> buf(new char[size]);
		file.readBytes(buf.get(), size);

		DynamicJsonBuffer jsonBuffer;
		JsonObject &json = jsonBuffer.parseObject(buf.get());
		if (!json.success()) {
			Serial.println(F("*** Configuration File Format Error ***"));
			return;
		}

		dsConfig(json);

		Serial.println(F("- Configuration loaded."));
	}

	// Validate it
	validateConfig();
}

// Serialize the current config into a JSON string
void serializeConfig(String &jsonString, bool pretty) {
	// Create buffer and root object
	DynamicJsonBuffer jsonBuffer;
	JsonObject &json = jsonBuffer.createObject();

	json["ssid"] = config.ssid.c_str();
	json["passphrase"] = config.passphrase.c_str();
	json["hostname"] = config.hostname.c_str();

	json["pixelCount"] = static_cast<uint8_t>(config.pixelCount);
	json["gamma"] = config.gamma;

	if (pretty)
		json.prettyPrintTo(jsonString);
	else
		json.printTo(jsonString);
}

// Save configuration JSON file
void saveConfig() {
	// Serialize Config
	String jsonString;
	serializeConfig(jsonString, true);

	// Save Config
	File file = SPIFFS.open(CONFIG_FILE, "w");
	if (!file) {
		Serial.println(F("*** Error creating configuration file ***"));
		return;
	} else {
		file.println(jsonString);
		Serial.println(F("* Configuration saved."));
	}
}


void setup() {
  Serial.begin(115200);
  while (!Serial);

  SPIFFS.begin();
  loadConfig();
  WiFi.hostname(config.hostname);
  animCtrl = new AnimationController(&mesh, config.pixelCount, config.gamma);

//mesh.setDebugMsgTypes( ERROR | MESH_STATUS | CONNECTION | SYNC | COMMUNICATION | GENERAL | MSG_TYPES | REMOTE ); // all types on
  mesh.setDebugMsgTypes( ERROR | STARTUP );  // set before init() so that you can see startup messages

  mesh.init( MESH_PREFIX, MESH_PASSWORD, &userScheduler, MESH_PORT );
  mesh.onReceive(&receivedCallback);
  mesh.onNewConnection(&newConnectionCallback);
  mesh.onChangedConnections(&changedConnectionCallback);
  mesh.onNodeTimeAdjusted(&nodeTimeAdjustedCallback);

  //TODO: initialize animationController

  userScheduler.addTask( taskSendMessage );
  taskSendMessage.enable();
}

void loop() {
  userScheduler.execute(); // it will run mesh scheduler as well
  mesh.update();
  animCtrl->update();
  //TODO: animationController update
}
