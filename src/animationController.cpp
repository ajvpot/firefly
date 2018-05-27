#include <NeoPixelBus.h>
#include "animationController.h"
#include "animations/blink.h"
#include "ArduinoJson.h"


AnimationController::AnimationController(painlessMesh* meshRef,
  uint16_t pixelCountIn, bool gammaSetting) {
    mesh = meshRef;
    gamma = gammaSetting;
    PixelCountChanged(pixelCountIn);


    StaticJsonBuffer<200> jsonBuffer;

    JsonObject& root = jsonBuffer.createObject();
    root["duration"] = 1000000;

    //JsonObject& jsonConfig = jsonBuffer.createObject();
    //jsonConfig["duration"] = (uint8_t)1000000;
    currentAnimation = new Blink(root, strip);

}

void AnimationController::PixelCountChanged(uint16_t pixelCount) {
  if(strip != NULL) {
    delete strip;
  }
  strip = new NeoPixelBus<NeoGrbFeature, Neo800KbpsMethod>(pixelCount);
  strip->Begin();
}

void AnimationController::update() {
  float_t animProg = (mesh->getNodeTime()%currentAnimation->getDuration())/(float_t)currentAnimation->getDuration();
  currentAnimation->render(animProg);
}
