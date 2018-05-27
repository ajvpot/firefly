#include "animationController.h"
#include "animation.h"
#include "arduinoJson.h"
#include "blink.h"

Blink::Blink(JsonObject config, NeoPixelBus<NeoGrbFeature, Neo800KbpsMethod>* stripRef) {
  //animationConfig.color = config["color"].as<RgbColor>();;
  animationConfig.duration = config["duration"].as<uint32_t>();;
  strip = stripRef;
}

uint32_t Blink::getDuration() {
  return animationConfig.duration;
}

void Blink::render(float_t progress) {
  if(progress >= 0.5) {
    strip->ClearTo(RgbColor(255,255,255));
  } else {
    strip->ClearTo(RgbColor(0,0,0));
  }
  strip->Show();;
}

/*Blink::Blink {
public:
  uint32_t baseDuration = 1000;
  // Sets the config
  struct AnimationConfig {
    RgbColor color;
    uint32_t duration;
  };

  // stores the config
  AnimationConfig animationConfig;

  // populates the config
  void dsState(JsonObject config) {
    //animationConfig.color = config["color"].as<RgbColor>();;
    animationConfig.duration = config["duration"].as<uint32_t>();;
  }

  // returns the duration of this instance
  uint32_t getDuration() {
    return animationConfig.duration;
  }

  void render(float_t progress) {
    if(progress >= 0.5) {

    }
  };
};
*/
