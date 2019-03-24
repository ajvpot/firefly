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
    void cut();
    void queue(Animation* newAnimation);
    Animation *animationFactory(int animationIndex, JsonObject &cfg);
  private:
    painlessMesh *mesh;
    bool gamma;
    NeoPixelBus<NeoGrbFeature, Neo800KbpsMethod> *strip = NULL;
    void PixelCountChanged(uint16_t pixelCount);
    Animation *currentAnimation;
    Animation *nextAnimation;
};
#endif
