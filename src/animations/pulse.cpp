#include "animationController.h"
#include "animation.h"
#include <ArduinoJson.h>
#include "pulse.h"

Pulse::Pulse(JsonObject& config, NeoPixelBus<NeoGrbFeature, Neo800KbpsMethod>* stripRef) {
  animationConfig.duration = config["duration"].as<uint32_t>();;
  strip = stripRef;
}

uint32_t Pulse::getDuration() {
  return animationConfig.duration;
}

void Pulse::render(float_t progress) {
  if(progress >= 0.5) {
    strip->ClearTo(RgbColor(int(progress*255)));
  } else {
    strip->ClearTo(RgbColor(255-int(progress*255)));
  }

  strip->Show();;
}
