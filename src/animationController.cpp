#include <NeoPixelBus.h>
#include "animationController.h"
#include "animations/blink.h"


AnimationController::AnimationController(painlessMesh* meshRef,
  uint16_t pixelCountIn, bool gammaSetting) {
    mesh = meshRef;
    gamma = gammaSetting;
    PixelCountChanged(pixelCountIn);

    JsonObject jsonConfig =
    currentAnimation = new Blink(jsonConfig, strip);

}

void AnimationController::PixelCountChanged(uint16_t pixelCount) {
  if(strip != NULL) {
    delete strip;
  }
  strip = new NeoPixelBus<NeoGrbFeature, Neo800KbpsMethod>(pixelCount);
  strip->Begin();
}

void AnimationController::update() {

  float_t animProg = (mesh->getNodeTime()%animTime)/(float_t)animTime;
}
