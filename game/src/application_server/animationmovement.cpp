#include "animationmovement.h"

#include <QStringList>
#include <QDebug>

/**
 * @brief AnimationMovement::AnimationMovement Erzeugt eine neue Bewegungsanimation.
 * @param pItem Das zu animierende Grafikitem.
 */
AnimationMovement::AnimationMovement(QGraphicsPixmapItem * pItem):
    item{pItem}
{

}

/**
 * @brief AnimationMovement::parsePath Liest einen Animationspfad aus einem String ein.
 * @param path Ein String im Format X1:Y1;X2:Y2;X3:Y3...
 */
void AnimationMovement::parsePath(QString data) {
    QStringList points = data.split(";");
    for(QString point : points){
        QStringList coords = point.split(":");
        path.push_back(new Point(coords[0].toInt(), coords[1].toInt()));
    }
    qDebug() << "Punkte eingelesen.";
    for(Point * p : path){
        qDebug() << "Punkt: " << p->getX() << " / " << p->getY();
    }
}

/**
 * @brief AnimationMovement::move Führt einen Schritt der Animation durch.
 */
bool AnimationMovement::move() {
    return true;
}
