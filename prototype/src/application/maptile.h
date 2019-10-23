#ifndef MAPTILE_H
#define MAPTILE_H

#include <QGraphicsPixmapItem>
#include "main.h"

class MapTile
{
public:
    enum TYPE{GRASS,FORREST,CITY, RIVER_H,RIVER_V,RIVER_LB,RIVER_LT,RIVER_RT,RIVER_RB};
    MapTile();
    void setType(TYPE pType);
    void setup(TYPE pType, int posX, int posY);
    bool isRiver();
    QGraphicsPixmapItem * getPixmapItem();

private:
    TYPE type;
    QGraphicsPixmapItem * pixmapItem;
};

#endif // MAPTILE_H
