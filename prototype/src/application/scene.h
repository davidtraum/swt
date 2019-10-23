#ifndef SCENE_H
#define SCENE_H

#include <QGraphicsScene>

#include "maptile.h"

class Scene: public QGraphicsScene
{
public:
    const static int MAP_SIZE{100}; //Die Größe der Karte. (In X und Y Richtung gleich groß)
    const static int TILE_SIZE{64}; //Die Abmessungen einer Kachel in Pixeln. Daher ist die reale Breite der Karte: MAP_SIZE*TILE_SIZE
    Scene();
    void generateWorld(); //Methode zur zufälligen Generierung der Karte
};

#endif // SCENE_H
