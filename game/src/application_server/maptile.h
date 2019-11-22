#ifndef MAPTILE_H
#define MAPTILE_H

#include <QGraphicsPixmapItem>
#include "city.h"
#include "graphicsmanager.h"

class MapTile
{
public:
    enum TYPE{GRASS,
              FORREST,
              CITY,
              RIVER_H,
              RIVER_V,
              RIVER_LB,
              RIVER_LT,
              RIVER_RT,
              RIVER_RB,
              RAIL_H,
              RAIL_V,
              RAIL_LB,
              RAIL_LT,
              RAIL_RT,
              RAIL_RB,
              WATER};
    MapTile(GraphicsManager * pGraphicsManager);
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
    int getX();
    int getY();
    void attachGraphicsManager(GraphicsManager * pGraphicsManager);

private:
    TYPE type;
    QGraphicsPixmapItem * pixmapItem;
    int currentRotation;
    City * city;
    GraphicsManager * graphicsManager;
};

#endif // MAPTILE_H
