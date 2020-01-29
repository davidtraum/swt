#include "scaleanimation.h"

#include <QDebug>
#include <cmath>

/**
 * @brief ScaleAnimation::ScaleAnimation Erzeugt eine neue Skalierungsanimation
 * @param pEntity Das AnimationsEntity.
 * @param pStart Der Startwert.
 * @param pEnd Der Endwert.
 * @param pSpeed Die Geschwindigkeit.
 */
ScaleAnimation::ScaleAnimation(AnimationEntity * pEntity, double pStart, double pEnd, double pSpeed):
    entity{pEntity}, start{pStart}, end{pEnd}, speed{pSpeed}
{
    entity->setScale(start);
}

/**
 * @brief ScaleAnimation::step Führt einen Animationsschritt durch.
 * @return true wenn die Animation fertig ist.
 */
bool ScaleAnimation::step()
{
    entity->setScale(entity->getScale()+speed);
    qDebug() << entity->getScale();
    if(abs(entity->getScale()-end) <= speed){
        return true;
    }else{
        return false;
    }
}
