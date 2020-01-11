#include "trainrenderer.h"

#include <QPainter>

TrainRenderer::TrainRenderer()
{
    QWidget::setFixedHeight(200);

}

void TrainRenderer::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    QWidget::paintEvent(event);
}


