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
    void keyReleaseEvent(QKeyEvent *event) override;

    void tick();

    void demo();

    Point mapPosition(int,int);
    Point toScreenPosition(int,int);
    Point getMinPos();
    Point getMaxPos();
    Point getTileCenter();

    void animateMovementToTilePosition(int,int);

    void setViewportTilePosition(int,int);

    void animateMovement(QImage, QString);
    void animateMovement(QImage, QString, double);

    MapTile data[300][300];
    Point offset{145*64,145*64};


private:
    GraphicsManager * graphicsManager;
    DataModel * dataModel;
    bool mouseDown{false};
    Point dragPosition{0,0};
    Point dragOrigin{0,0};
    Point activeTile{0,0};
    bool showHighlight{false};
    bool rendering{false};
    long renderTime{0};
    double scale{1};
    bool showExpertDetails{false};
    QList<AnimationMovement *> movementAnimations;
    long lastFpsTake{0};
    int frameCount{0};
    int fps{0};
    double vx{0},vy{0};
    int moveStepsLeft{0};
    int tileSize{64};
    int originTileSize{64};
    int halfSize{tileSize/2};

public slots:
    void onTileChange(int,int,int);
    void enableHighlight(bool);

signals:
    void tileClick(int,int,int);
    void leftclick();
    void positionChange(int,int);
};

#endif // MAPRENDERER_H
