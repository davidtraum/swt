#ifndef VIEW_H
#define VIEW_H

#include <QGraphicsView>

class View: public QGraphicsView
{
public:
    View();
    int dragOriginX,dragOriginY;
    double currentScale{1.0};
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
};

#endif // VIEW_H
