#include "trainrenderer.h"

#include <QPainter>
#include <QDebug>

TrainRenderer::TrainRenderer(GraphicsManager * pGm):
    graphicsManager{pGm}
{
    QWidget::setFixedHeight(200);

    train = QImage(":/images/train/train.png");

}

void TrainRenderer::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    int width = 208;
    int paintX = 255;
    for(std::pair<const std::string, int> key : wagons){
       for(int i = 0; i<key.second; i++){
           painter.drawImage(paintX, 0, graphicsManager->get((key.first)).toImage());
           paintX += width;
       }
    }

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


