#include "minimap.h"
#include <QPaintEvent>
#include <QPainter>
#include <QDebug>
#include <QRectF>

Minimap::Minimap(int pWidth, int pHeight, Scene * pScene, DataModel * pDataModel):
    width{pWidth}, height{pHeight}, scene{pScene}, dataModel{pDataModel}
{
    QWidget::setFixedSize(width,height);
    QWidget::setStyleSheet("background-color: white");
    connect(dataModel, &DataModel::viewChange, this, &Minimap::viewChange);
}

void Minimap::paintEvent(QPaintEvent *event)
{
    qDebug() << "Repaint";
    QPainter painter(this);
    for(int x = 0; x<300; x++){
        for(int y = 0; y<300; y++){
            MapTile::TYPE type = scene->data[x][y].getType();
            switch(type){
                case MapTile::GRASS:
                case MapTile::FORREST:
                    painter.setPen(Qt::green);
                    break;
                case MapTile::CITY:
                    painter.setPen(Qt::black);
                    break;
                default:
                    painter.setPen(Qt::green);
                    if(scene->data[x][y].isRiver()){
                        painter.setPen(Qt::blue);
                    }
                    break;
            }
            painter.drawPoint(x,y);
        }
    }
    painter.setPen(Qt::red);
    painter.drawImage(QRectF(dataModel->getHoverX()-16, dataModel->getHoverY()-16,32,32), QImage(":/icons/location.svg"));
}

void Minimap::viewChange(){
    repaint(0,0,width,height);
}
