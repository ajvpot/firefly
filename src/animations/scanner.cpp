#include "animationController.h"
#include "animation.h"
#include <ArduinoJson.h>
#include "scanner.h"

Scanner::Scanner(JsonObject& config, NeoPixelBus<NeoGrbFeature, Neo800KbpsMethod>* stripRef) {
  //animationConfig.color = config["color"].as<RgbColor>();;
  animationConfig.duration = config["duration"].as<uint32_t>();;
  strip = stripRef;
} // color duration size speed

uint32_t Scanner::getDuration() {
  return animationConfig.duration;
}
// SetPixelColor
void Scanner::render(float_t progress) {
  strip->ClearTo(RgbColor(255,255,255));
  int progressMin = progress * 30; // beginning of eye
  int progressMax = progressMin + animationConfig.size; // end of eye
  for(int i = 0; i < 30; i++) {
    if(i >= progressMin && i <= progressMax) {
      strip->SetPixelColor(i, animationConfig.color);
    }
  }

  strip->Show();;
}
