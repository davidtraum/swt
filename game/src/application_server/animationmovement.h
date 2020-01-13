#ifndef ANIMATIONMOVEMENT_H
#define ANIMATIONMOVEMENT_H

#include "point.h"
#include <QList>
#include <QString>
#include <QGraphicsPixmapItem>

class AnimationMovement
{
public:
    AnimationMovement(QGraphicsPixmapItem *);
    void parsePath(QString path);
    bool move();

private:
    QGraphicsPixmapItem * item;
    QList<Point *> path;
    int pointIndex{0};

};

#endif // ANIMATIONMOVEMENT_H