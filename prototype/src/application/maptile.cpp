#include "maptile.h"
#include <QDebug>
#include <QBrush>
#include <QColor>

/**
 * @brief MapTile::MapTile Konstruktor.
 */
MapTile::MapTile()
{
    pixmapItem = new QGraphicsPixmapItem();
    currentRotation = 0;
}

/**
 * @brief MapTile::setType Setzt den Typ der Kachel.
 * @param pType Der Typ.
 */
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
            pixmapItem->setToolTip("Schiene");
            break;
    }
    type = pType;
}

/**
 * @brief MapTile::getType Liefert den Typ des Quadranten.
 * @return Den Typ.
 */
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

/**
 * @brief MapTile::getRotation Liefert die aktuelle Rotation. (Himmelsrichtung)
 * @return Die aktuelle Rotation (0-3)
 */
int MapTile::getRotation(){
    return currentRotation;
}



/**
 * @brief MapTile::isRiver Checkt ob die Kachel ein Fluss ist.
 * @return Ob die Kachel ein Fluss ist.
 */
bool MapTile::isRiver(){
    return type!=MapTile::TYPE::RIVER_H
            && type!=MapTile::TYPE::RIVER_V
            && type!=MapTile::TYPE::RIVER_LB
            && type!=MapTile::TYPE::RIVER_LT
            && type!=MapTile::TYPE::RIVER_RB
            && type!=MapTile::TYPE::RIVER_RT;
}

/**
 * @brief MapTile::setPosition Setzt die Position der Kachel. (In Pixeln)
 * @param posX Die X Koordinate.
 * @param posY Die Y Koordinate.
 */
void MapTile::setPosition(int posX, int posY){
    pixmapItem->setPos(posX, posY);
}

/**
 * @brief MapTile::getPixmapItem Liefert das Pixmap Item.
 * @return Das Pixmap Item.
 */
QGraphicsPixmapItem * MapTile::getPixmapItem(){
    return pixmapItem;
}


