#include "animationController.h"
#include "animation.h"
#include <ArduinoJson.h>
#include "colorWipe.h"

ColorWipe::ColorWipe(JsonObject& config, NeoPixelBus<NeoGrbFeature, Neo800KbpsMethod>* stripRef) {
  //animationConfig.color = config["color"].as<RgbColor>();;
  animationConfig.duration = config["duration"].as<uint32_t>();;
  strip = stripRef;
} // color duration size speed

uint32_t ColorWipe::getDuration() {
  return animationConfig.duration;
}
// SetPixelColor
void ColorWipe::render(float_t progress) {
  strip->ClearTo(RgbColor(255,255,255));
  int progressMin = progress * 30; // max of strip color
  for(int i = 0; i < 30; i++) {
    if(i <= progressMin) {
      strip->SetPixelColor(i, animationConfig.color);
    }
  }

  strip->Show();;
}
