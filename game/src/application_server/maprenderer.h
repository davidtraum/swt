#ifndef MAPRENDERER_H
#define MAPRENDERER_H

#include <QWidget>
#include <QList>
#include <QThread>
#include <QVideoWidget>
#include <QMediaPlayer>
#include <QMediaPlaylist>

#include "graphicsmanager.h"
#include "datamodel.h"
#include "maptile.h"
#include "point.h"
#include "animationmovement.h"
#include "sprite.h"
#include "mousedecor.h"

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
    void logicUpdate();
    void renderFrame();


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

    void cloudAnimation();
    void bridgeAnimation();
    void spawnCloud();

    void animateScale(double);

    MapTile data[300][300];
    Point offset{145*64,145*64};
    int codeCount;

    //Sprite * testSprite;

private:
    GraphicsManager * graphicsManager;
    DataModel * dataModel;
    bool mouseDown{false};
    Point dragPosition{0,0};
    Point dragOrigin{0,0};
    Point activeTile{0,0};
    double offsetTargetX{145*64},offsetTargetY{145*64};
    bool showHighlight{false};
    bool rendering{false};
    long renderTime{0};
    double scale{1};
    bool showExpertDetails{false};
    QList<AnimationMovement *> movementAnimations;
    long lastFpsTake{0};
    int frameCount{0};
    int ticksSkipped{0};
    int timeToRender{0};
    int timeSinceCloudSpawn{0};
    int framerateDelay{20};
    int fps{0};
    double vx{0},vy{0};
    int moveStepsLeft{0};
    int scaleStepsLeft{0};
    double scaleVector;
    int tileSize{64};
    int originTileSize{64};
    int ea1c{0};
    int halfSize{tileSize/2};
    QPixmap * buffer;
    QMediaPlayer * videoPlayer;
    QVideoWidget * videoWidget;

public slots:
    void onTileChange(int,int,int);
    void enableHighlight(bool);
    void setLogicSpeed(int);
private slots:
    void onVideoStateChange(QMediaPlayer::State);

signals:
    void tileClick(int,int,int);
    void leftclick();
    void positionChange(int,int);
    void sendPlayBridge();
};

#endif // MAPRENDERER_H
