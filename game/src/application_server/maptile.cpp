#include "maptile.h"
#include <QDebug>
#include <QBrush>
#include <QColor>

/**
 * @brief MapTile::MapTile Konstruktor.
 */
MapTile::MapTile(GraphicsManager * pGraphicsManager)
{
    graphicsManager = pGraphicsManager;
    MapTile();
}

/**
 * @brief MapTile::MapTile Konstruktor.
 */
MapTile::MapTile(){
    pixmapItem = new QGraphicsPixmapItem();
    currentRotation = 0;
    city = nullptr;
}

/**
 * @brief MapTile::attachGraphicsManager Setzte den GraphicsManager.
 * @param pGraphicsManager Ein GraphicsManager.
 */
void MapTile::attachGraphicsManager(GraphicsManager *pGraphicsManager){
    graphicsManager = pGraphicsManager;
}

/**
 * @brief MapTile::setType Setzt den Typ der Kachel.
 * @param pType Der Typ.
 */
void MapTile::setType(MapTile::TYPE pType){
    switch(pType){
        case MapTile::TYPE::GRASS:
            pixmapItem->setPixmap(graphicsManager->get("grass"));
            pixmapItem->setToolTip("Leere Grasfläche");
            break;
        case MapTile::TYPE::FORREST:
            pixmapItem->setPixmap(graphicsManager->get("wald"));
            pixmapItem->setToolTip("Wald");
            break;
        case MapTile::TYPE::CITY:
            pixmapItem->setPixmap(graphicsManager->get("stadt"));
            pixmapItem->setToolTip("Stadt");
            break;


        case MapTile::TYPE::RIVER_H:
            pixmapItem->setPixmap(graphicsManager->get("fluss_h"));
            break;
        case MapTile::TYPE::RIVER_V:
            pixmapItem->setPixmap(graphicsManager->get("fluss_v"));
            break;
        case MapTile::TYPE::RIVER_LT:
            pixmapItem->setPixmap(graphicsManager->get("fluss_lt"));
            break;
        case MapTile::TYPE::RIVER_LB:
            pixmapItem->setPixmap(graphicsManager->get("fluss_lb"));
            break;
        case MapTile::TYPE::RIVER_RT:
            pixmapItem->setPixmap(graphicsManager->get("fluss_rt"));
            break;
        case MapTile::TYPE::RIVER_RB:
            pixmapItem->setPixmap(graphicsManager->get("fluss_rb"));
            break;

        case MapTile::TYPE::RAIL_H:
            pixmapItem->setPixmap(graphicsManager->get("schiene_h"));
            pixmapItem->setToolTip("Schiene");
            break;
        case MapTile::TYPE::WATER:
            pixmapItem->setPixmap(graphicsManager->get("water"));
            pixmapItem->setToolTip("Meer");
            break;
    }
    type = pType;
    setRotation(0);
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

/**
 * @brief MapTile::getCity Die Informationen. Falls keine Stadt: null
 * @return Liefert die Informationen über eine Stadt auf der Kachel.
 */
City * MapTile::getCity(){
    return city;
}

/**
 * @brief MapTile::setCity
 * @param pCity Fügt dem Quadranten Daten über eine Stadt hinzu.
 */
void MapTile::setCity(City * pCity){
    city = pCity;
}

/**
 * @brief MapTile::getX
 * @return Der X Index des Quadranten.
 */
int MapTile::getX(){
    return int(pixmapItem->x()/64);
}
/**
 * @brief MapTile::getY
 * @return Der Y Index des Quadranten.
 */
int MapTile::getY(){
    return int(pixmapItem->y()/64);
}


