#include "view.h"

#include <QMouseEvent>
#include <QDebug>
#include <QPointF>

View::View()
{
    QGraphicsView::setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    QGraphicsView::setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    QGraphicsView::setCursor(QCursor(Qt::CrossCursor));
}


void View::mousePressEvent(QMouseEvent *event){
    View::dragOriginX = event->x();
    View::dragOriginY = event->y();
}

void View::mouseReleaseEvent(QMouseEvent *event)
{
    QGraphicsView::setCursor(QCursor(Qt::CrossCursor));
}

void View::mouseMoveEvent(QMouseEvent *event)
{
    QPointF sceneCenter = QGraphicsView::mapToScene( QGraphicsView::viewport()->rect().center() );
    sceneCenter.setX(sceneCenter.x() - (event->x() - View::dragOriginX));
    sceneCenter.setY(sceneCenter.y() - (event->y() - View::dragOriginY));
    QGraphicsView::centerOn(sceneCenter);
    View::dragOriginX = event->x();
    View::dragOriginY = event->y();
    QGraphicsView::setCursor(QCursor(Qt::PointingHandCursor));
}

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
}

void View::keyPressEvent(QKeyEvent *event){
    if(event->text()[0]=='g'){

    }
}
