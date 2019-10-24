#include "view.h"

#include <QMouseEvent>
#include <QDebug>
#include <QPointF>
#include <QString>
#include <QGraphicsItem>

/**
 * @brief View::View Konstruktor. Versteckt u.a. die Scrollbars und aktiviert Mousetracking.
 * @param pScene Das Zugehörige Szenenobjekt.
 */
View::View(Scene * pScene)
{
    scene = pScene;
    QGraphicsView::setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    QGraphicsView::setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    QGraphicsView::setCursor(QCursor(Qt::CrossCursor));
    QGraphicsView::setMouseTracking(true);
    mouseDown = false;
}


/**
 * @brief View::mousePressEvent QT Methode. Wird aufgerufen wenn die Maus gedrückt wurde.
 * @param event Enthält Informationen über die Taste und Position.
 */
void View::mousePressEvent(QMouseEvent *event){
    View::dragOriginX = event->x();
    View::dragOriginY = event->y();
    View::dragPosX = View::dragOriginX;
    View::dragPosY = View::dragOriginY;
    mouseDown = true;
}


/**
 * @brief View::mouseReleaseEvent QT Methode. Wird aufgerufen wenn die Maus losgelassen wird.
 * @param event Informationen über Position und Taste
 */
void View::mouseReleaseEvent(QMouseEvent *event)
{
    QGraphicsView::setCursor(QCursor(Qt::CrossCursor));
    if(View::dragOriginX==event->x() && View::dragOriginY==event->y()){ //Es wurde nur geklickt, nicht verschoben.
        QGraphicsItem * clickedItem = View::itemAt(event->pos());
        MapTile * clickedTile = scene->getTileAt(int(clickedItem->x()), int(clickedItem->y()), true); //Der Quadrant der angeklickt wurde.
        if(event->button() == Qt::LeftButton){ //Linksklick
            if(clickedTile->getType() == MapTile::TYPE::GRASS){
                clickedTile->setType(MapTile::TYPE::RAIL_H);
            }
            qDebug() << "[EVENT] Linksklick.";
        }else{ //Rechtsklick
            if(clickedTile->getType()==MapTile::TYPE::RAIL_H){
                int currentRotation = clickedTile->getRotation();
                currentRotation++;
                if(currentRotation>3)currentRotation=0;
                clickedTile->setRotation(currentRotation);
            }
            qDebug() << "[EVENT] Rechtsklick.";
        }

    }else{
        qDebug() << "[EVENT] Karte verschoben";
    }
    mouseDown = false;
}

/**
 * @brief View::mouseMoveEvent QT Methode. Wird aufgerufen wenn die Maus bewegt wird.
 * @param event Informationen über Position der Maus
 */
void View::mouseMoveEvent(QMouseEvent *event)
{
    if(mouseDown){
        QPointF sceneCenter = QGraphicsView::mapToScene( QGraphicsView::viewport()->rect().center() );
        sceneCenter.setX(sceneCenter.x() - (event->x() - View::dragPosX));
        sceneCenter.setY(sceneCenter.y() - (event->y() - View::dragPosY));
        QGraphicsView::centerOn(sceneCenter);
        View::dragPosX = event->x();
        View::dragPosY = event->y();
        QGraphicsView::setCursor(QCursor(Qt::PointingHandCursor));
    }else{
        scene->setActiveTile(QGraphicsView::itemAt(event->pos()));
    }
}

/**
 * @brief View::wheelEvent QT Methode. Wird aufgerufen wenn das Mausrad gedreht wird.
 * @param event Eventobjekt mit Infos. Wichtig: event->delta(): Positiv oder negativ jenachdem in welche Richtung gedreht wurde.
 */
void View::wheelEvent(QWheelEvent *event)
{
   if(event->delta()>0){
       if(View::currentScale<3){
           View::currentScale*=1.1;
       }
   }else{
       if(View::currentScale>0.1){
          View::currentScale*=0.9;
       }
   }
   QGraphicsView::resetMatrix();
   QGraphicsView::scale(View::currentScale, View::currentScale);
   qDebug() << "[EVENT] Skalierung geändert.";
}

/**
 * @brief View::keyPressEvent QT Methode. Wird Aufgerufen wenn eine Taste gedrückt wird.
 * @param event Event mit Informationen. Wichtig: event->text(): Text der Taste und event->key(): Id der Taste
 */
void View::keyPressEvent(QKeyEvent *event){
    if(event->text()[0]=='g'){

    }
}
