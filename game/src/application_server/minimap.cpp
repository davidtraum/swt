#include "minimap.h"
#include <QPaintEvent>
#include <QPainter>
#include <QDebug>
#include <QRectF>

/**
 * @brief Minimap::Minimap Erzeugt eine neue Minimap Komponente
 * @param pWidth Die Breite der Minimap in Pixeln
 * @param pHeight Die Höhe der Minimap in Pixeln
 * @param pScene Die Szene
 * @param pDataModel Das DataModel
 */
Minimap::Minimap(int pWidth, int pHeight, MapRenderer  * pScene, DataModel * pDataModel):
    width{pWidth}, height{pHeight}, scene{pScene}, dataModel{pDataModel}
{
    QWidget::setFixedSize(width,height);
    QWidget::setStyleSheet("border: 2px solid black;");
    connect(dataModel, &DataModel::viewChange, this, &Minimap::viewChange);

    location = QImage(":/icons/pin.svg");
    location_white = QImage(":/icons/pin_white.svg");
    compass = QImage(":/images/highres/kompass.png");
    mapOverlay = QImage(":/images/highres/map_overlay.png");
    setStyleSheet("border: 2px solid black");

    renderMap();

    show();
}

/**
 * @brief Minimap::paintEvent Rendert die Minimap.
 * @param event Das zugehörige Event.
 */
void Minimap::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    painter.drawImage(0,0,map);

    painter.setPen(Qt::red);
    painter.drawImage(QRectF(dataModel->getHoverX()-16, dataModel->getHoverY()-28,32,32), location);
    painter.drawImage(QRectF(dataModel->secondPlayer->posX-16, dataModel->secondPlayer->posY-28,32,32), location_white);
    painter.drawImage(QRectF(10,10, 280, 280), compass);
    painter.drawImage(0,0,mapOverlay);
    painter.drawRect(0,0,299,299);
    QWidget::paintEvent(event);
}

/**
 * @brief Minimap::renderMap Erzeugt das Bild von der aktuellen Karte.
 */
void Minimap::renderMap()
{
    QPixmap * pixmap = new QPixmap(300,300);
    QPainter painter(pixmap);

    for(int x = 0; x<300; x++){
        for(int y = 0; y<300; y++){
            MapTile::TYPE type = scene->data[x][y].getType();
            switch(type){
                case MapTile::CITY:
                    painter.setPen(Qt::black);
                    break;
                case MapTile::RIVER_H:
                case MapTile::RIVER_V:
                case MapTile::RIVER_LB:
                case MapTile::RIVER_LT:
                case MapTile::RIVER_RB:
                case MapTile::RIVER_RT:
                    painter.setPen(Qt::blue);
                    break;
                case MapTile::RAIL_H:
                case MapTile::RAIL_V:
                case MapTile::RAIL_LB:
                case MapTile::RAIL_LT:
                case MapTile::RAIL_RB:
                case MapTile::RAIL_RT:
                    painter.setPen(Qt::black);
                    break;
                default:
                    painter.setPen(Qt::green);
                    break;
            }
            painter.drawPoint(x,y);
        }
    }

    painter.end();
    map = pixmap->toImage();
    delete pixmap;
}

/**
 * @brief Minimap::viewChange Slot der aufgerufen wird wenn die Minimap komplett neu gezeichnet werden soll.
 */
void Minimap::viewChange(){
    renderMap();
}
