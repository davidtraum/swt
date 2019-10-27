#ifndef MAPTILE_H
#define MAPTILE_H

#include <QGraphicsPixmapItem>
#include "main.h"

class MapTile
{
public:
    enum TYPE{GRASS,FORREST,CITY, RIVER_H,RIVER_V,RIVER_LB,RIVER_LT,RIVER_RT,RIVER_RB, RAIL_H};
    MapTile();
    void setType(TYPE pType);
    TYPE getType();
    void setRotation(int pRotation);
    int getRotation();
    void setPosition(int posX, int posY);
    bool isRiver();
    QGraphicsPixmapItem * getPixmapItem();

private:
    TYPE type;
    QGraphicsPixmapItem * pixmapItem;
    int currentRotation;
};

#endif // MAPTILE_H
