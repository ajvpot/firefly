#include "animationController.h"
#include "animation.h"
#include <ArduinoJson.h>
#include "lightWave.h"

LightWave::LightWave(JsonObject& config, NeoPixelBus<NeoGrbFeature, Neo800KbpsMethod>* stripRef) {
  animationConfig.duration = config["duration"].as<uint32_t>();;
  strip = stripRef;
  animationConfig.position = 0; // position + rate
}

uint32_t LightWave::getDuration() {
  return animationConfig.duration;
}

void LightWave::render(float_t progress) {
  animationConfig.position++;
  strip->ClearTo(RgbColor(0,0,0));
  for(int i = 0; i < 30; i++) {
    RgbColor color = RgbColor(((sin(i+animationConfig.position) * 127 + 128) / 255),
    ((sin(i+animationConfig.position) * 127 + 128) / 255),
    ((sin(i+animationConfig.position) * 127 + 128) / 255)
  );
    strip->SetPixelColor(i, color);
  }

  strip->Show();;
}
