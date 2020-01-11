#ifndef ANIMATIONMANAGER_H
#define ANIMATIONMANAGER_H

#include "animationmovement.h"
#include <QList>
#include <QGraphicsPixmapItem>

class AnimationManager
{
public:
    AnimationManager();
    void tick();
    void animateMovement(QGraphicsPixmapItem *, QString);

private:
    QList<AnimationMovement *> movementAnimations;
};

#endif // ANIMATIONMANAGER_H
