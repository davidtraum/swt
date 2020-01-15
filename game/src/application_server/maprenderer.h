#ifndef MAPRENDERER_H
#define MAPRENDERER_H

#include <QWidget>
#include <QList>

#include "graphicsmanager.h"
#include "datamodel.h"
#include "maptile.h"
#include "point.h"
#include "animationmovement.h"

class MapRenderer: public QWidget
{
    Q_OBJECT
public:
    MapRenderer(GraphicsManager *, DataModel *);

    void paintEvent(QPaintEvent *event) override;

    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;

    void tick();

    void demo();

    Point mapPosition(int,int);
    Point toScreenPosition(int,int);
    Point getMinPos();
    Point getMaxPos();

    void animateMovement(QImage, QString);
    void animateMovement(QImage, QString, double);

    MapTile data[300][300];
    Point offset{0,0};


private:
    GraphicsManager * graphicsManager;
    DataModel * dataModel;
    bool mouseDown{false};
    Point dragPosition{0,0};
    Point dragOrigin{0,0};
    Point activeTile{0,0};
    bool showHighlight{false};
    bool rendering{false};
    double scale{1};
    QList<AnimationMovement *> movementAnimations;

public slots:
    void onTileChange(int,int,int);
    void enableHighlight(bool);

signals:
    void tileClick(int,int,int);
    void leftclick();
};

#endif // MAPRENDERER_H
