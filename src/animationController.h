// animation controller

#include <NeoPixelBus.h>
#include "painlessMesh.h"
#include "arduinoJson.h"

NeoPixelBus<NeoGrbFeature, Neo800KbpsMethod> strip(PixelCount);

class AnimationController {
  public:
    painlessMesh mesh;
    uint32_t duration;
    uint32_t curTime;
    void update();
};

class Animation {
  public:
    virtual void render(float_t progress);
    virtual void setState(JsonObject config);
    uint32_t baseDuration;
};
