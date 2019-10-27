#ifndef MAPTILE_H
#define MAPTILE_H

#include <QGraphicsPixmapItem>
#include "main.h"
#include "city.h"

class MapTile
{
public:
    enum TYPE{GRASS,FORREST,CITY, CITY_CENTER, RIVER_H,RIVER_V,RIVER_LB,RIVER_LT,RIVER_RT,RIVER_RB, RAIL_H};
    MapTile();
    void setType(TYPE pType);
    TYPE getType();
    void setRotation(int pRotation);
    int getRotation();
    void setPosition(int posX, int posY);
    bool isRiver();
    QGraphicsPixmapItem * getPixmapItem();
    City * getCity();
    void setCity(City * pCity);

private:
    TYPE type;
    QGraphicsPixmapItem * pixmapItem;
    int currentRotation;
    City * city;
};

#endif // MAPTILE_H
