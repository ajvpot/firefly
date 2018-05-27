// animation controller
#ifndef animationController_h
#define animationController_h
#include <NeoPixelBus.h>
#include "painlessMesh.h"
#include "arduinoJson.h"
#include "animation.h"

class AnimationController {
  public:
    AnimationController(painlessMesh* mesh, uint16_t pixelCount, bool gamma);
    void update();
  private:
    painlessMesh* mesh;
    bool gamma;
    NeoPixelBus<NeoGrbFeature, Neo800KbpsMethod>* strip = NULL;
    void PixelCountChanged(uint16_t pixelCount);
    Animation* currentAnimation;
};
#endif
