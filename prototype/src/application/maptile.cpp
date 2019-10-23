#include "maptile.h"
#include <QDebug>
#include <QBrush>
#include <QColor>

MapTile::MapTile()
{
    pixmapItem = new QGraphicsPixmapItem();
}

void MapTile::setType(MapTile::TYPE pType){
    switch(pType){
        case MapTile::TYPE::GRASS:
            pixmapItem->setPixmap(graphics->GRAPHICS["grass"]);
            break;
        case MapTile::TYPE::FORREST:
            pixmapItem->setPixmap(graphics->GRAPHICS["wald"]);
            break;
        case MapTile::TYPE::CITY:
            pixmapItem->setPixmap(graphics->GRAPHICS["stadt"]);
            break;

        case MapTile::TYPE::RIVER_H:
            pixmapItem->setPixmap(graphics->GRAPHICS["fluss_h"]);
            break;
        case MapTile::TYPE::RIVER_V:
            pixmapItem->setPixmap(graphics->GRAPHICS["fluss_v"]);
            break;
        case MapTile::TYPE::RIVER_LT:
            pixmapItem->setPixmap(graphics->GRAPHICS["fluss_lt"]);
            break;
        case MapTile::TYPE::RIVER_LB:
            pixmapItem->setPixmap(graphics->GRAPHICS["fluss_lb"]);
            break;
        case MapTile::TYPE::RIVER_RT:
            pixmapItem->setPixmap(graphics->GRAPHICS["fluss_rt"]);
            break;
        case MapTile::TYPE::RIVER_RB:
            pixmapItem->setPixmap(graphics->GRAPHICS["fluss_rb"]);
            break;
    }
    type = pType;
}

bool MapTile::isRiver(){
    return type!=MapTile::TYPE::RIVER_H
            && type!=MapTile::TYPE::RIVER_V
            && type!=MapTile::TYPE::RIVER_LB
            && type!=MapTile::TYPE::RIVER_LT
            && type!=MapTile::TYPE::RIVER_RB
            && type!=MapTile::TYPE::RIVER_RT;
}

void MapTile::setup(MapTile::TYPE pType, int posX, int posY){
    setType(pType);
    pixmapItem->setPos(posX, posY);
}

QGraphicsPixmapItem * MapTile::getPixmapItem(){
    return pixmapItem;
}


