#ifndef ANIMATIONENTITY_H
#define ANIMATIONENTITY_H

#include <QImage>
#include "point.h"

class AnimationEntity
{
public:
    AnimationEntity(QImage *, int,int);
    AnimationEntity(QImage *, int id = -1);
    Point getPosition();
    void move(double,double);
    double getX();
    double getY();
    void setPosition(int,int);
    QImage * getImage();
    bool autoRotate{true};
    int rotation{0};
    int getId();
private:
    QImage * image;
    int id{-1};
    double x{0},y{0};
};

#endif // ANIMATIONENTITY_H
