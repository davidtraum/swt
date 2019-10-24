#include "maptile.h"
#include <QDebug>
#include <QBrush>
#include <QColor>

MapTile::MapTile()
{
    pixmapItem = new QGraphicsPixmapItem();
    currentRotation = 0;
}

void MapTile::setType(MapTile::TYPE pType){
    switch(pType){
        case MapTile::TYPE::GRASS:
            pixmapItem->setPixmap(graphics->GRAPHICS["grass"]);
            pixmapItem->setToolTip("Leere Grasfläche");
            break;
        case MapTile::TYPE::FORREST:
            pixmapItem->setPixmap(graphics->GRAPHICS["wald"]);
            pixmapItem->setToolTip("Wald");
            break;
        case MapTile::TYPE::CITY:
            pixmapItem->setPixmap(graphics->GRAPHICS["stadt"]);
            pixmapItem->setToolTip("Stadt");
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

        case MapTile::TYPE::RAIL_H:
            pixmapItem->setPixmap(graphics->GRAPHICS["schiene_h"]);
            break;
    }
    type = pType;
}

MapTile::TYPE MapTile::getType(){
    return type;
}

/**
 * @brief MapTile::setRotation Hilfsfunktion zur Rotation im Quadrat.
 * @param pRotation 0=Ursprung 1=90° Grad 2=180° Grad 3=270°
 */
void MapTile::setRotation(int pRotation){
    pixmapItem->setTransformOriginPoint(32,32);
    switch(pRotation){
        case 1:
            pixmapItem->setRotation(90);
            break;
        case 2:
            pixmapItem->setRotation(180);
            break;
        case 3:
            pixmapItem->setRotation(270);
            break;
        default:
            pixmapItem->setRotation(0);
            break;
    }
    currentRotation = pRotation;
}

int MapTile::getRotation(){
    return currentRotation;
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


