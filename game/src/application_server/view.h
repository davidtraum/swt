#ifndef VIEW_H
#define VIEW_H

#include <QGraphicsView>
#include "scene.h"
#include "datamodel.h"
#include "tooltipmenu.h"

class View: public QGraphicsView
{
    Q_OBJECT
public:
    Scene * scene;
    View(Scene * pScene, ToolTipMenu * pToolTip);
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
    void setDataModel(DataModel * pModel);
    void tick();
private:
    DataModel * dataModel;
    int dragOriginX,dragOriginY,dragPosX,dragPosY,mouseX,mouseY;
    bool mouseDown;
    bool doAnimations;
    ToolTipMenu * tooltip;
    void leftclick(QMouseEvent *, MapTile *);
    void rightclick(QMouseEvent *, MapTile *);

signals:
    void onLeftclick();

public slots:
    void zoomInAnimation();

};

#endif // VIEW_H
