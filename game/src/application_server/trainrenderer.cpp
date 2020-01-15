#include "trainrenderer.h"

#include <QPainter>
#include <QDebug>
#include <QMouseEvent>

TrainRenderer::TrainRenderer(GraphicsManager * pGm):
    graphicsManager{pGm}
{
    QWidget::setFixedHeight(200);

    train = QImage(":/images/train/train.png");
    background = QImage(":/images/train/train_background.png");
    sky = QImage(":/images/train/train_sky.png");
    wagon = QImage(":/images/train/wagon.png");

}

void TrainRenderer::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    painter.fillRect(0,0,this->width(), this->height(), QBrush(background));
    painter.drawImage(0, this->height()-200,background);
    int width = 208;
    int wagonWidth = 255;
    int paintX = 305;
    int paintY = 0;
    int componentWidth = QWidget::width();
    for(std::pair<const std::string, int> key : wagons){
       for(int i = 0; i<key.second; i++){
           if(paintX + wagonWidth > componentWidth){
               paintX = 0;
               paintY += 200;
           }
           painter.drawImage(paintX, paintY+90 , wagon);
           painter.drawImage(paintX+130, paintY+100, QImage((":/icons/icon_" + QString::fromStdString(key.first))).scaled(64,64));
           paintX += width;
       }
    }

    QWidget::setFixedHeight
            (paintY + 200);

    painter.drawImage(50,90,train);
    QWidget::paintEvent(event);
}

void TrainRenderer::addWagon(std::string name)
{
    if(wagons[name] == 0){
        wagons[name] = 1;
    }else{
        wagons[name]++;
    }
    QWidget::repaint();
}

void TrainRenderer::deleteAllWagons()
{
    wagons.clear();
    QWidget::repaint();
}

void TrainRenderer::mouseReleaseEvent(QMouseEvent *event)
{
    int x = event->x();
    int y = event->y();
    int paintX = 208;
    int paintY = 0;
    for(std::pair<const std::string, int> key : wagons){
        if(x > paintX && x<paintX+255 && y > paintY && y < paintY+200){
            wagons.erase(key.first);
            QWidget::repaint();
            return;
        }
        paintX+=255;
        if(paintX+255 > this->width()){
            paintX = 0;
            paintY += 200;
        }
    }

    triggerRemoveWagon();
}

void triggerRemoveWagon() {
    emit triggerRemoveWagon();
}


