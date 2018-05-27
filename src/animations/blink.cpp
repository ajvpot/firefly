//asdf
#include "animationController.h"
#include "arduinoJson.h"

class Blink : public Animation {
public:
  uint32_t baseDuration = 1000;
  // Sets the config
  struct AnimationConfig {
    RgbColor color;
  };

  // stores the config
  AnimationConfig animationConfig;

  // populates the config
  void setState(JsonObject config) {
    animationConfig.color = config["color"];
  }

  void render(float_t progress) {
    if(progress >= 0.5) {
      
    }
  };
};
