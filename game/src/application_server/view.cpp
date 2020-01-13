#include "view.h"

#include <QMouseEvent>
#include <QDebug>
#include <QPointF>
#include <QString>
#include <QGraphicsItem>
#include <QTimer>
#include <QMessageBox>
#include <QIcon>
#include <QGraphicsItem>
#include <QPalette>
#include <QUrl>


/**
 * @brief View::View Konstruktor. Versteckt u.a. die Scrollbars und aktiviert Mousetracking.
 * @param pScene Das Zugehörige Szenenobjekt.
 */
View::View(Scene * pScene, ToolTipMenu * pToolTip) :
    tooltip{pToolTip}, scene{pScene}
{
    QGraphicsView::setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    QGraphicsView::setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    QGraphicsView::setCursor(QCursor(Qt::CrossCursor));
    QGraphicsView::setMouseTracking(true);
    mouseDown = false;
    doAnimations = false;
    mouseX = 0;
    mouseY = 0;
    codeCount=0;

    /*
    mediaPlayer = new QMediaPlayer(this);
    videoItem = new QGraphicsVideoItem();
    mediaPlayer->setVideoOutput(videoItem);
    scene->addItem(videoItem);
    videoItem->show();
    mediaPlayer->setMedia(QUrl("https://traum.me/ameland/ameland_2019_low.mp4"));
    mediaPlayer->play();
   */
}


/**
 * @brief View::mousePressEvent QT Methode. Wird aufgerufen wenn die Maus gedrückt wurde.
 * @param event Enthält Informationen über die Taste und Position.
 */
void View::mousePressEvent(QMouseEvent *event) {
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
            qDebug() << "[EVENT] Linksklick.";
            leftclick(event, clickedTile);
        }else{ //Rechtsklick
            qDebug() << "[EVENT] Rechtsklick.";
            rightclick(event, clickedTile);
        }

    }else{
        qDebug() << "[EVENT] Karte verschoben";
    }
    mouseDown = false;
}

/**
 * @brief View::leftclick Führt einen Linksklick aus.
 */
void View::leftclick(QMouseEvent * pEvent, MapTile * pTile)
{
    switch(dataModel->getMode()){
        case DataModel::DEFAULT:
            //kein Zoom, wenn Bahnhof geklickt (RouteInterface)
            if (pTile->getType() == MapTile::TERMINAL_H || pTile->getType() == MapTile::TERMINAL_V ||pTile->getType() == MapTile::DEPOT_H||pTile->getType() == MapTile::DEPOT_V||pTile->getType() == MapTile::STATION_H||pTile->getType() == MapTile::STATION_V)
                break;
            doAnimations = true;
            fluidZoom(1, currentScale<1);
            fluidMovement(pTile->getX()*64, pTile->getY()*64);
            break;
        default:
            break;
    }
    emit onLeftclick();
    switch(pTile->getType()){
        case MapTile::TERMINAL_H:
        case MapTile::TERMINAL_V:
        case MapTile::DEPOT_H:
        case MapTile::DEPOT_V:
        case MapTile::STATION_H:
        case MapTile::STATION_V:
            emit onTrainStationClick(pTile->getX(), pTile->getY());
            break;
    }
}




/**
 * @brief View::leftclick Führt einen Rechtsklick aus.
 */
void View::rightclick(QMouseEvent * pEvent, MapTile * pTile)
{
    emit onRightclick();
}

/**
 * @brief View::tick Asynchroner Tick. Wird alle 20MS von GameLoop aufgerufen.
 */
void View::tick(){
    /*
    QPointF sceneCenter = QGraphicsView::mapToScene( QGraphicsView::viewport()->rect().center() );
    double vectorX = (dataModel->getHoverX()*64 - sceneCenter.x()) * 0.01;
    double vectorY = (dataModel->getHoverY()*64 - sceneCenter.y()) * 0.01;
    sceneCenter.setX(sceneCenter.x() + vectorX);
    sceneCenter.setY(sceneCenter.y() + vectorY);
    qDebug() << vectorY;
    View::centerOn(sceneCenter);
    */
}

/**
 * @brief View::mouseMoveEvent QT Methode. Wird aufgerufen wenn die Maus bewegt wird.
 * @param event Informationen über Position der Maus
 */
void View::mouseMoveEvent(QMouseEvent *event)
{
    if(mouseDown){
        tooltip->hide();
        QPointF sceneCenter = QGraphicsView::mapToScene( QGraphicsView::viewport()->rect().center() );
        sceneCenter.setX(sceneCenter.x() - ((event->x() - View::dragPosX - 1.2) * 1.0/currentScale));   //"-1.2" gleicht 'Drall' nach oben links aus
        sceneCenter.setY(sceneCenter.y() - ((event->y() - View::dragPosY -1.2) * 1.0/currentScale));
        QGraphicsView::centerOn(sceneCenter);
        View::dragPosX = event->x();
        View::dragPosY = event->y();
        QGraphicsView::setCursor(QCursor(Qt::DragMoveCursor));
        doAnimations = false;
    }else{
        QGraphicsItem * hoverItem = QGraphicsView::itemAt(event->pos());
        dataModel->updateCoordinates(int(hoverItem->x()/64), int(hoverItem->y()/64));
        MapTile * tile = scene->getTileAt(hoverItem->x(), hoverItem->y(), true);
        if(tile->getType() == MapTile::CITY){
            tooltip->setText("<h2>Haus</h2> <p><img height=\"16\" src=\":/icons/Nahrung.svg\"></img> 100</p>");
            tooltip->showAt(event->x()+10, event->y()+10);
        }else{
            tooltip->hide();
        }
        scene->setActiveTile(hoverItem);
    }
}

/**
 * @brief View::wheelEvent QT Methode. Wird aufgerufen wenn das Mausrad gedreht wird.
 * @param event Eventobjekt mit Infos. Wichtig: event->delta(): Positiv oder negativ jenachdem in welche Richtung gedreht wurde.
 */
void View::wheelEvent(QWheelEvent *event)
{
    tooltip->hide();
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
    qDebug() << "[EVENT] Tastatur gedrückt. ";
    switch(event->key()){
        case Qt::Key_F11:
        /*
            if(mainWindow->isFullScreen()){
                mainWindow->showNormal();
            }else{
                mainWindow->showFullScreen();
            }
            break;
            */
        case Qt::Key_O:
            if(currentScale>0.06){
                doAnimations=true;
                fluidZoom(0.06, false);
            }
            break;

        case Qt::Key_Left:
            fluidMove(-128,0);
            if (codeCount == 4 || codeCount == 6)
                codeCount++;
            else
                codeCount = 0;
            break;
        case Qt::Key_Right:
            fluidMove(128,0);
            if (codeCount == 5 || codeCount == 7)
                codeCount++;
            else
                codeCount = 0;
            break;
        case Qt::Key_Up:
            fluidMove(0,-128);
            if (codeCount == 0 || codeCount == 1)
                codeCount++;
            else
                codeCount = 0;
            break;
        case Qt::Key_Down:
            fluidMove(0,128);
            if (codeCount == 2 || codeCount == 3)
                codeCount++;
            else
                codeCount = 0;
            break;
        case Qt::Key_B:
            if (codeCount == 8)
                codeCount++;
            else
                codeCount = 0;
            break;
        case Qt::Key_A:
            if (codeCount == 9)
                codeCount++;
            else
                codeCount = 0;
            break;
        default:
            codeCount = 0;
        break;

    }

    qDebug() << "codeCount " << QString::number(codeCount);

    //Hier gibt es nichts zu sehen:
    if (codeCount == 10) {
        qDebug("KONAMI CODE");
        QWidget* box = new QWidget();
        box->setWindowModality(Qt::ApplicationModal);
        box->setWindowTitle("Thomas And Friends");

        QHBoxLayout* layout = new QHBoxLayout();
        box->setLayout(layout);

        QPixmap p(":/images/thomasAndFriends.png");
        QLabel * image = new QLabel(this);
        image->setPixmap(p.scaled(800, 800,Qt::KeepAspectRatio, Qt::FastTransformation));

        layout->addWidget(image);
        image->show();
        box->show();
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


/**
 * @brief View::setDataModel Setzt das Datenmodell. An dieses wird dann kontinuierlich die aktuelle Position weitergegeben.
 * @param pModel Ein Datenmodell.
 */
void View::setDataModel(DataModel *pModel){
    dataModel = pModel;
}

/**
 * @brief View::paintEvent Überschreibt das PaintEvent des Views für eigene Zeichenanweisungen.
 * @param event Das zugehörige QPaintEvent.
 */
void View::paintEvent(QPaintEvent *event)
{
    QPainter painter(QGraphicsView::viewport());
    //Hier zeichenanweisungen einfügen.
    QGraphicsView::paintEvent(event);
}


/**
 * @brief View::zoomInAnimation Slot der nach dem Laden der Karte aufgerufen wird.
 */
void View::zoomInAnimation(){
    QTimer::singleShot(1000, [this]{
        this->enableAnimation();
        this->fluidZoom(1, true);
    });
}
