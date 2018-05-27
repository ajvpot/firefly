#ifndef animation_h
#define animation_h
#include "animationController.h"

class Animation {
  public:
    virtual void render(float_t progress);
    //virtual void dsState(JsonObject config);
    virtual uint32_t getDuration();
  private:
    AnimationController* controller;
};
#endif
