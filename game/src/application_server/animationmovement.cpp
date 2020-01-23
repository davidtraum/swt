#include "animationmovement.h"

#include <QStringList>
#include <QDebug>
#include <math.h>

/**
 * @brief AnimationMovement::AnimationMovement Erzeugt eine neue Bewegungsanimation.
 * @param pItem Das zu animierende Grafikitem.
 */
AnimationMovement::AnimationMovement(AnimationEntity * pItem, QString pPath):
    item{pItem}
{
    parsePath(pPath);
}

/**
 * @brief AnimationMovement::parsePath Liest einen Animationspfad aus einem String ein.
 * @param path Ein String im Format X1:Y1;X2:Y2;X3:Y3...
 */
void AnimationMovement::parsePath(QString data) {
    QStringList points = data.split(";");
    for(QString point : points){
        QStringList coords = point.split(":");
        path.push_back(new Point(coords[0].toInt()*64, coords[1].toInt()*64));
    }
    qDebug() << "Punkte eingelesen.";
    for(Point * p : path){
        qDebug() << "Punkt: " << p->getX() << " / " << p->getY();
    }
}

AnimationEntity *AnimationMovement::getEntity()
{
    return item;
}

/**
 * @brief AnimationMovement::move Führt einen Schritt der Animation durch.
 */
bool AnimationMovement::move() {
    if(pointIndex==-1){
        item->setPosition(path.first()->getX(), path.first()->getY());
        pointIndex=1;
        calculateVector(0,1);
    }else{
        item->move(vx, vy);
        if(targetDistance() <= speed){
            int before = pointIndex;
            pointIndex++;
            if(pointIndex>=path.length()){
                pointIndex = 0;
                if(!repeat){
                    return true;
                }
            }
            calculateVector(before, pointIndex);
        }
    }
    return false;
}

/**
 * @brief AnimationMovement::setRepeat Setzt ob die Animation in Endlosschleife läuft.
 * @param pStatus true = endlos, false = einmalig
 */
void AnimationMovement::setRepeat(bool pStatus)
{
    repeat = pStatus;
}

/**
 * @brief AnimationMovement::setSpeed Setzt die Geschwindigkeit der Animation.
 * @param pSpeed Die Geschwindigkeit (1=normal, 2=doppelt...)
 */
void AnimationMovement::setSpeed(double pSpeed)
{
    speed = pSpeed;
}

/**
 * @brief AnimationMovement::setAutoRotate Setzt ob sich das Bild automatisch in Bewegungsrichtung drehen soll.
 */
void AnimationMovement::setAutoRotate(bool pStatus)
{
    autoRotate = pStatus;
}

void AnimationMovement::calculateVector(Point origin, Point target)
{
    int vxt = target.getX() - origin.getX();
    int vyt = target.getY() - origin.getY();
    double len = sqrt(vxt*vxt + vyt*vyt);
    vx = vxt/len;
    vy = vyt/len;
    if(item->autoRotate && autoRotate){
        if(abs(vx) > abs(vy)){
            if(vx<0){
                item->rotation = 270;
            }else{
                item->rotation = 90;
            }
        }else{
            if(vy>0){
                item->rotation = 180;
            }else{
                item->rotation = 0;
            }
        }
    }
    vx*=speed;
    vy*=speed;
}

void AnimationMovement::calculateVector(int origin, int target)
{
    calculateVector(*path.at(origin), *path.at(target));
}

double AnimationMovement::targetDistance()
{
    Point target = *path.at(pointIndex);
    double dvx = target.getX() - item->getX();
    double dvy = target.getY() - item->getY();
    return sqrt(dvx*dvx + dvy*dvy);
}
