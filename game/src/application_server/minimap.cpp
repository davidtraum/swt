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
Minimap::Minimap(int pWidth, int pHeight, Scene * pScene, DataModel * pDataModel):
    width{pWidth}, height{pHeight}, scene{pScene}, dataModel{pDataModel}
{
    QWidget::setFixedSize(width,height);
    QWidget::setStyleSheet("border: 2px solid black;");
    connect(dataModel, &DataModel::viewChange, this, &Minimap::viewChange);

    location = QImage(":/icons/pin.svg");
    compass = QImage(":/images/highres/compass.png");
}

/**
 * @brief Minimap::paintEvent Rendert die Minimap.
 * @param event Das zugehörige Event.
 */
void Minimap::paintEvent(QPaintEvent *event)
{
    qDebug() << "Repaint";
    QPainter painter(this);
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
                default:
                    painter.setPen(Qt::green);
                    break;
            }
            painter.drawPoint(x,y);
        }
    }
    painter.setPen(Qt::red);
    painter.drawImage(QRectF(dataModel->getHoverX()-16, dataModel->getHoverY()-28,32,32), QImage(":/icons/pin.svg"));
    painter.drawImage(QRectF(0,0,width,height), compass);
}

/**
 * @brief Minimap::viewChange Slot der aufgerufen wird wenn die Minimap komplett neu gezeichnet werden soll.
 */
void Minimap::viewChange(){
    repaint(0,0,width,height);
}
