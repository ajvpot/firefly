// animation controller

#include <NeoPixelBus.h>
#include "painlessMesh.h"
#include "arduinoJson.h"

class AnimationController {
  public:
    painlessMesh* mesh;
    bool gamma;
    NeoPixelBus<NeoGrbFeature, Neo800KbpsMethod>* strip = NULL;

    void PixelCountChanged(uint16_t pixelCount) {
      if(strip != NULL) {
        delete strip;
      }
      strip = new NeoPixelBus<NeoGrbFeature, Neo800KbpsMethod>(pixelCount);
      strip->Begin();
    }

    void update() {
      //float_t animProg = (mesh.getNodeTime()%animTime)/(float_t)animTime;
    }
};

class Animation {
  public:
    AnimationController* controller;
    virtual void render(float_t progress);
    virtual void setState(JsonObject config);
    virtual uint32_t getDuration();
};
