//asdf
#ifndef lightWave_h
#define lightWave_h
#include "animationController.h"
#include "animation.h"
#include "arduinoJson.h"

class LightWave : public Animation {
public:
  LightWave(JsonObject& config, NeoPixelBus<NeoGrbFeature, Neo800KbpsMethod>* strip);
private:
  // Sets the config
  struct AnimationConfig {
    RgbColor color;
    uint32_t duration;
    uint16_t position;
  };
  // stores the config
  AnimationConfig animationConfig;

  // stores the strip reference
  NeoPixelBus<NeoGrbFeature, Neo800KbpsMethod>* strip;

  uint32_t getDuration();
  void render(float_t progress);
};
#endif
