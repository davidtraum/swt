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
              WATER,
              DEPOT_H,
              DEPOT_V,
              STATION_H,
              STATION_V,
              TERMINAL_H,
              TERMINAL_V,
              BRIDGE_H,
              BRIDGE_V,
              CORN,
              COAL,
              WOOD,
              FOOD,
              LIVESTOCK,
              GOODS,
              PETROLEUM,
              PAPER,
              STEEL};
    MapTile(GraphicsManager * pGraphicsManager);
    MapTile();
    void setType(TYPE pType);
    TYPE getType();
    void setRotation(int pRotation);
    int getRotation();
    int getRotationDeg();
    void setPosition(int posX, int posY);
    bool isRiver();
    bool isRail();
    QGraphicsPixmapItem * getPixmapItem();
    City * getCity();
    void setCity(City * pCity);
    int getX();
    int getY();
    void attachGraphicsManager(GraphicsManager * pGraphicsManager);

private:
    TYPE type;
    QGraphicsPixmapItem * pixmapItem;
    int currentRotation{0};
    City * city;
    GraphicsManager * graphicsManager;

signals:
    void playBridge();
};

#endif // MAPTILE_H
