#include "trainrenderer.h"

#include <QPainter>
#include <QDebug>

TrainRenderer::TrainRenderer(GraphicsManager * pGm):
    graphicsManager{pGm}
{
    QWidget::setFixedHeight(200);

    train = QImage(":/images/train/train.png");
    background = QImage(":/images/train/train_background.png");
    sky = QImage(":/images/train/train_sky.png");

}

void TrainRenderer::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    int width = 208;
    int wagonWidth = 255;
    int paintX = 255;
    int paintY = 0;
    int componentWidth = QWidget::width();
    for(std::pair<const std::string, int> key : wagons){
       //painter.drawImage(0,paintY, background);
       for(int i = 0; i<key.second; i++){
           if(paintX + wagonWidth > componentWidth){
               paintX = 0;
               paintY += 200;
           }
           painter.drawImage(paintX, paintY , graphicsManager->get((key.first)).toImage());
           paintX += width;
       }
    }

    QWidget::setFixedHeight
            (paintY + 200);

    painter.drawImage(0,0,train);
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

void TrainRenderer::mouseReleaseEvent(QMouseEvent *event)
{
    addWagon("corn");
}


