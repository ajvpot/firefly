//asdf
#include "animationController.cpp"
#include "arduinoJson.h"

class Blink : public Animation {
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
  void setState(JsonObject config) {
    animationConfig.color = config["color"];
    animationConfig.duration = config["duration"];
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
