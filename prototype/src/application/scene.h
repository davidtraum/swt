#ifndef SCENE_H
#define SCENE_H

#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <QGraphicsItem>
#include <QGraphicsRectItem>

#include "maptile.h"

class Scene: public QGraphicsScene
{
public:
    const static int MAP_SIZE{300}; //Die Größe der Karte. (In X und Y Richtung gleich groß)
    const static int TILE_SIZE{64}; //Die Abmessungen einer Kachel in Pixeln. Daher ist die reale Breite der Karte: MAP_SIZE*TILE_SIZE
    QGraphicsRectItem * highlighter;
    MapTile * activeTile;
    MapTile data[Scene::MAP_SIZE][Scene::MAP_SIZE];
    Scene();
    void generateWorld(); //Methode zur zufälligen Generierung der Karte
    void setActiveTile(QGraphicsItem * pItem);
    MapTile * getTileAt(int posX, int posY, bool isPixelCoordinate);
};

#endif // SCENE_H
