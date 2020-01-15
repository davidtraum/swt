#ifndef ANIMATIONMOVEMENT_H
#define ANIMATIONMOVEMENT_H

#include "point.h"
#include "animationentity.h"
#include <QList>
#include <QString>
#include <QGraphicsPixmapItem>

class AnimationMovement
{
public:
    AnimationMovement(AnimationEntity *, QString);
    void parsePath(QString path);
    AnimationEntity * getEntity();
    bool move();
    void setSpeed(double);

private:
    void calculateVector(Point origin, Point target);
    void calculateVector(int origin, int target);
    double targetDistance();
    double speed{1};
    AnimationEntity * item;
    QList<Point *> path;
    double vx{0},vy{0};
    int pointIndex{-1};

};

#endif // ANIMATIONMOVEMENT_H
