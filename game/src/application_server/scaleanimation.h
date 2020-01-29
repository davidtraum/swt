#ifndef SCALEANIMATION_H
#define SCALEANIMATION_H

#include "animationentity.h"

class ScaleAnimation
{
public:
    ScaleAnimation(AnimationEntity *, double, double, double);
    AnimationEntity * entity;
    double start,end,speed;
    bool step();
};

#endif // SCALEANIMATION_H
