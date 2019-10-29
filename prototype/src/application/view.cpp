#include "view.h"

#include <QMouseEvent>
#include <QDebug>
#include <QPointF>
#include <QString>
#include <QGraphicsItem>
#include <QTimer>
#include <QMessageBox>
#include <QIcon>

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
    doAnimations = false;
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
    doAnimations = false;
    QGraphicsView::setCursor(QCursor(Qt::CrossCursor));
    if(View::dragOriginX==event->x() && View::dragOriginY==event->y()){ //Es wurde nur geklickt, nicht verschoben.
        QGraphicsItem * clickedItem = View::itemAt(event->pos());
        MapTile * clickedTile = scene->getTileAt(int(clickedItem->x()), int(clickedItem->y()), true); //Der Quadrant der angeklickt wurde.
        if(event->button() == Qt::LeftButton){ //Linksklick
            if(clickedTile->getType() == MapTile::TYPE::GRASS){
                clickedTile->setType(MapTile::TYPE::RAIL_H);
            }else if(clickedTile->getType() == MapTile::CITY){
                    City * city = clickedTile->getCity();
                    doAnimations = true;
                    fluidMovement(city->getCenterX()*64, city->getCenterY()*64);
                    fluidZoom(0.5, currentScale<0.5);

            }
            qDebug() << "[EVENT] Linksklick.";
        }else{ //Rechtsklick
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
        sceneCenter.setX(sceneCenter.x() - ((event->x() - View::dragPosX) * 1.0/currentScale));
        sceneCenter.setY(sceneCenter.y() - ((event->y() - View::dragPosY) * 1.0/currentScale));
        QGraphicsView::centerOn(sceneCenter);
        View::dragPosX = event->x();
        View::dragPosY = event->y();
        QGraphicsView::setCursor(QCursor(Qt::PointingHandCursor));
        doAnimations = false;
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
    qDebug() << "[EVENT] Tastatur gedrückt.";
    switch(event->key()){
        case Qt::Key_F11:
            if(mainWindow->isFullScreen()){
                mainWindow->showNormal();
            }else{
                mainWindow->showFullScreen();
            }
            break;
        case Qt::Key_O:
            if(currentScale>0.06){
                doAnimations=true;
                fluidZoom(0.06, false);
            }
            break;

        case Qt::Key_Left:
            fluidMove(-128,0);
            break;
        case Qt::Key_Right:
            fluidMove(128,0);
            break;
        case Qt::Key_Up:
            fluidMove(0,-128);
            break;
        case Qt::Key_Down:
            fluidMove(0,128);
            break;
    }

    if(event->key() == Qt::Key_F11){

    }
}

/**
 * @brief View::fluidZoom Startet eine Zoom-Animation. Zuvor muss doAnimations=true gesetzt sein. Bsp: fluidZoom(3, true) zoomt 3x in die Karte hinein.
 * @param target Die angestrebte Skalierung.
 * @param in Ob vergrößert oder verkleindert werden soll. (true = reinzoomen, false=rauszoomen).
 */
void View::fluidZoom(double target, bool in){
    if(!doAnimations){
        qDebug() << "[ANIMATION] Zoom abgebrochen";
        return;
    }
    resetMatrix();
    if(in){
        currentScale+=0.01;
        if(currentScale < target){
            QTimer::singleShot(10, [this,target,in]{fluidZoom(target,in);});
        }else{
            qDebug() << "[ANIMATION] Zoom abgeschlossen.";
        }
    }else{
        currentScale-=0.05;
        if(currentScale > target){
            QTimer::singleShot(10, [this,target,in]{fluidZoom(target,in);});
        }else{
            qDebug() << "[ANIMATION] Zoom abgeschlossen.";
        }
    }
    scale(currentScale, currentScale);
}

/**
 * @brief View::fluidMove Verschiebt die Karte animiert und relativ zur aktuellen Position.
 * @param vX Verschiebung in X-Richtung.
 * @param vY Verschiebung in Y-Richtung.
 */
void View::fluidMove(int vX, int vY){
    doAnimations = true;
    QPointF sceneCenter = QGraphicsView::mapToScene( QGraphicsView::viewport()->rect().center() );
    fluidMovement(int(sceneCenter.x() + vX), int(sceneCenter.y() + vY));
}

/**
 * @brief View::fluidMovement Verschiebt die Karte animiert an zu einer absoluten Koordinate.
 * @param pX Die X-Koordinate.
 * @param pY Due Y-Koordinate.
 */
void View::fluidMovement(int pX, int pY){
    if(!doAnimations){
        qDebug() << "[ANIMATION] Bewegung abgebrochen.";
        return;
    }
    QPointF sceneCenter = QGraphicsView::mapToScene( QGraphicsView::viewport()->rect().center() );
    int diffX = int(pX<sceneCenter.x() ? sceneCenter.x()-pX : pX-sceneCenter.x());
    int diffY = int(pY<sceneCenter.y() ? sceneCenter.y()-pY : pY-sceneCenter.y());
        if(diffX > 64) sceneCenter.setX(sceneCenter.x()-(sceneCenter.x()-pX)*0.1);
        if(diffY > 64) sceneCenter.setY(sceneCenter.y()-(sceneCenter.y()-pY)*0.1);
        View::centerOn(sceneCenter);
        if((diffX > 64 || diffY>64)){
          QTimer::singleShot(10, [this,pX,pY]{fluidMovement(pX,pY);});
        }else{
            qDebug() << "[ANIMATION] Bewegung abgeschlossen.";
        }
}

/**
 * @brief View::enableAnimation Aktiviert animationen bis zum nächsten Event.
 */
void View::enableAnimation(){
    doAnimations = true;
}
