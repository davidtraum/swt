#include "animationentity.h"

/**
 * @brief AnimationEntity::AnimationEntity Erzeugt ein neues Animation-Entity.
 * @param pImage Das Bild.
 * @param pX Die X-Startposition.
 * @param pY Die Y-Startposition.
 */
AnimationEntity::AnimationEntity(QImage * pImage, int pX, int pY):
    image{pImage}
{
    x = int(pX);
    y = int(pY);
}

AnimationEntity::AnimationEntity(QImage * pImage, int pId):
    image{pImage}, id{pId}
{

}

/**
 * @brief AnimationEntity::getPosition Liefert die Position.
 * @return Die Position als Point.
 */
Point AnimationEntity::getPosition()
{
    return Point(int(x),int(y));
}

/**
 * @brief AnimationEntity::move Verschiebt das Element um einen Vektor.
 * @param vx Die X-Komponente.
 * @param vy Die Y-Komponente.
 */
void AnimationEntity::move(double vx, double vy)
{
    x+=vx;
    y+=vy;
}

double AnimationEntity::getX()
{
    return x;
}

double AnimationEntity::getY()
{
    return y;
}

/**
 * @brief AnimationEntity::setPosition Setzt die Position des Elements.
 */
void AnimationEntity::setPosition(int px, int py)
{
    x = px;
    y = py;
}

/**
 * @brief AnimationEntity::getImage Liefert die Grafik des Animationselements.
 * @return Ein QImage.
 */
QImage *AnimationEntity::getImage()
{
    return image;
}

/**
 * @brief AnimationEntity::getId Liefert die ID zurück.
 * @return Die Animationsid.
 */
int AnimationEntity::getId()
{
    return id;
}



