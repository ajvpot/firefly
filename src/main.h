#include <Arduino.h>
#include <vector>
#include <ArduinoJson.h>

/* Configuration structure */
typedef struct {
    /* Network */
    String      ssid;
    String      passphrase;
    String      hostname;

    /* Strip config */
    uint16_t    pixelCount;
    bool        gamma;          /* Use gamma map? */
} config_t;

/* Forward Declarations */
void serializeConfig(String &jsonString, bool pretty = false);
void dsConfig(JsonObject &json);
void saveConfig();

/* Animation state structure */
typedef struct {
  uint16_t type;
  uint16_t duration;
  uint16_t param1;
  uint16_t param2;
} animState_t;

/* Forward Declarations */
void serializeAnimState(String &jsonString, bool pretty = false);
animState_t dsAnimState(String &jsonString);
