#ifndef VIEW_H
#define VIEW_H

#include <QGraphicsView>
#include "main.h"
#include "scene.h"

class View: public QGraphicsView
{
public:
    Scene * scene;
    View(Scene * pScene);
    int dragOriginX,dragOriginY,dragPosX,dragPosY;
    bool mouseDown;
    double currentScale{1.0};
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void fluidZoom(double target, bool in);
    void fluidMove(int vX, int vY);
    void fluidMovement(int pX, int pY);
    void enableAnimation();
private:
    bool doAnimations;
};

#endif // VIEW_H
