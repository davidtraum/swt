#ifndef ANIMATIONMOVEMENT_H
#define ANIMATIONMOVEMENT_H

#include "point.h"
#include "animationentity.h"
#include <QList>
#include <QString>
#include <QObject>
#include <QGraphicsPixmapItem>

class AnimationMovement: public QObject
{
    Q_OBJECT
public:
    AnimationMovement(AnimationEntity *, QString);
    void parsePath(QString path);
    AnimationEntity * getEntity();
    bool move();
    void setRepeat(bool);
    void setSpeed(double);
    void setAutoRotate(bool);
    void setEmitChanges(bool);

private:
    void calculateVector(Point origin, Point target);
    void calculateVector(int origin, int target);
    double targetDistance();
    bool repeat{true};
    bool autoRotate{true};
    bool emitChanges{false};
    int direction{1};
    double speed{1};
    AnimationEntity * item;
    QList<Point *> path;
    double vx{0},vy{0};
    int pointIndex{-1};

signals:
    void reachedPoint(int,int,AnimationMovement *);

};

#endif // ANIMATIONMOVEMENT_H
