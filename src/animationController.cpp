#include <NeoPixelBus.h>
#include "animationController.h"
#include "animations/blink.h"
#include "ArduinoJson.h"


AnimationController::AnimationController(painlessMesh* meshRef,
  uint16_t pixelCountIn, bool gammaSetting) {
    Serial.println(F("AnimationController::AnimationController(...): Call"));
    mesh = meshRef;
    gamma = gammaSetting;
    Serial.println(F("AnimationController::AnimationController(...): init strip"));
    PixelCountChanged(pixelCountIn);

    Serial.println(F("AnimationController::AnimationController(...): gen test json"));
    StaticJsonBuffer<200> jsonBuffer;

    JsonObject& root = jsonBuffer.createObject();
    root["duration"] = 1000000;

    //JsonObject& jsonConfig = jsonBuffer.createObject();
    //jsonConfig["duration"] = (uint8_t)1000000;
    Serial.println(F("AnimationController::AnimationController(...): init blink"));
    currentAnimation = new Blink(root, strip);

}

void AnimationController::PixelCountChanged(uint16_t pixelCount) {
  Serial.print(F("AnimationController::PixelCountChanged(...): pixelcount is"));
  Serial.println(pixelCount);
  if(strip != NULL) {
    Serial.println(F("AnimationController::PixelCountChanged(...): strip is not NULL"));
    delete strip;
  }
  Serial.println(F("AnimationController::PixelCountChanged(...): init strip"));
  strip = new NeoPixelBus<NeoGrbFeature, Neo800KbpsMethod>(pixelCount);
  Serial.println(F("AnimationController::PixelCountChanged(...): begin strip"));
  //TODO: debug
  strip->Begin();
  strip->ClearTo(255);
  strip->Show();
  delay(100);

}

void AnimationController::update() {
  float_t animProg = (mesh->getNodeTime()%currentAnimation->getDuration())/(float_t)currentAnimation->getDuration();
  currentAnimation->render(animProg);
}
