#ifndef SCENE_H
#define SCENE_H

#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <QGraphicsItem>
#include <QGraphicsRectItem>
#include <QGraphicsEllipseItem>

#include "maptile.h"
#include "graphicsmanager.h"
#include "player.h"

class Scene: public QGraphicsScene
{
    Q_OBJECT
public:
    const static int MAP_SIZE{300}; //Die Größe der Karte. (In X und Y Richtung gleich groß)
    const static int TILE_SIZE{64}; //Die Abmessungen einer Kachel in Pixeln. Daher ist die reale Breite der Karte: MAP_SIZE*TILE_SIZE
    Scene(GraphicsManager * pGraphicsManager);
    void generateWorld(); //Methode zur zufälligen Generierung der Karte
    void setActiveTile(QGraphicsItem * pItem);
    MapTile * getTileAt(int posX, int posY, bool isPixelCoordinate=false);
    void setTileAt(int,int,int,int);
    void tileChanged(int,int);

private:
    MapTile data[Scene::MAP_SIZE][Scene::MAP_SIZE];
    QGraphicsRectItem * highlighter;
    QGraphicsEllipseItem * radiusHighlighter;
    QGraphicsTextItem * textHint;
    bool showRadius;
    MapTile * activeTile;
    GraphicsManager * graphicsManager;
    std::map<int, Player *> players;
public slots:
    void onSetTile(int,int,int,int);
    void updatePlayerPosition(int, int,int);
    void addPlayer(int);

signals:
    void tileUpdate(int,int,int,int);
};

#endif // SCENE_H
