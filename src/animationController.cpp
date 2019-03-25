#include <NeoPixelBus.h>
#include "animationController.h"
#include "animations/blink.h"
#include "animations/colorWipe.h"
#include "animations/lightWave.h"
#include "animations/pulse.h"
#include "animations/scanner.h"
#include "ArduinoJson.h"

AnimationController::AnimationController(painlessMesh *meshRef,
                                         uint16_t pixelCountIn, bool gammaSetting)
{
  Serial.println(F("AnimationController::AnimationController(...): Call"));
  mesh = meshRef;
  gamma = gammaSetting;
  Serial.println(F("AnimationController::AnimationController(...): init strip"));
  PixelCountChanged(pixelCountIn);

  Serial.println(F("AnimationController::AnimationController(...): gen test config"));
  StaticJsonBuffer<200> jsonBuffer;
  JsonObject &root = jsonBuffer.createObject();
  root["duration"] = 1000000;

  Serial.println(F("AnimationController::AnimationController(...): init blink"));
  queue(new Blink(root, strip));
  cut();
  //currentAnimation = new Blink(root, strip);
}

void AnimationController::PixelCountChanged(uint16_t pixelCount)
{
  Serial.print(F("AnimationController::PixelCountChanged(...): pixelcount is"));
  Serial.println(pixelCount);
  if (strip != NULL)
  {
    Serial.println(F("AnimationController::PixelCountChanged(...): strip is not NULL"));
    delete strip;
  }
  Serial.println(F("AnimationController::PixelCountChanged(...): init strip"));
  strip = new NeoPixelBus<NeoGrbFeature, Neo800KbpsMethod>(pixelCount);
  Serial.println(F("AnimationController::PixelCountChanged(...): begin strip"));
  //TODO: debug
  strip->Begin();
  strip->ClearTo(255);
  strip->Show();
  delay(100);
}

void AnimationController::update()
{
  float_t animProg = (mesh->getNodeTime() % currentAnimation->getDuration()) / (float_t)currentAnimation->getDuration();
  currentAnimation->render(animProg);
}

void AnimationController::queue(Animation *newAnimation)
{
  Serial.println(F("AnimationController::queue(...)"));
  nextAnimation = newAnimation;
}

void AnimationController::cut()
{
  Serial.println(F("AnimationController::cut(...)"));
  auto oldAnimation = currentAnimation;
  currentAnimation = nextAnimation;
}
// later: crossfade? new Crossfade(cfg, strip, animA, animB)

Animation* AnimationController::animationFactory(int animationIndex, JsonObject &cfg)
{
  switch (animationIndex)
  {
  //blink
  case 0:
  {
    return new Blink(cfg, strip);
    break;
  }

  //colorWipe
  case 1:
  {
    return new ColorWipe(cfg, strip);
    break;
  }
  
  //lightWave
  case 2:
  {
    return new LightWave(cfg, strip);
    break;
  }
  
  //pulse
  case 3:
  {
    return new Pulse(cfg, strip);
    break;
  }
  
  //scanner
  case 4:
  {
    return new Scanner(cfg, strip);
    break;
  }
  }
  return NULL;
}