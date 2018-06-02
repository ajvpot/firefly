//asdf
#ifndef colorWipe_h
#define colorWipe_h
#include "animationController.h"
#include "animation.h"
#include "arduinoJson.h"

class ColorWipe : public Animation {
public:
  ColorWipe(JsonObject& config, NeoPixelBus<NeoGrbFeature, Neo800KbpsMethod>* strip);
private:
  // Sets the config
  struct AnimationConfig {
    RgbColor color;
    uint32_t duration;
    uint16_t size;
    uint16_t speed;
  };
  // stores the config
  AnimationConfig animationConfig;

  // stores the strip reference
  NeoPixelBus<NeoGrbFeature, Neo800KbpsMethod>* strip;

  uint32_t getDuration();
  void render(float_t progress);
};
#endif
