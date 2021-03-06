#include "maptile.h"
#include <QDebug>
#include <QBrush>
#include <QColor>
#include <QMediaPlayer>
#include <QVideoWidget>

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
    setRotation(0);
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
            setRotation(0);
            break;
        case MapTile::TYPE::RIVER_V:
            pixmapItem->setPixmap(graphicsManager->get("fluss_v"));
            setRotation(0);
            break;
        case MapTile::TYPE::RIVER_LT:
            pixmapItem->setPixmap(graphicsManager->get("fluss_lt"));
            setRotation(0);
            break;
        case MapTile::TYPE::RIVER_LB:
            pixmapItem->setPixmap(graphicsManager->get("fluss_lb"));
            setRotation(0);
            break;
        case MapTile::TYPE::RIVER_RT:
            pixmapItem->setPixmap(graphicsManager->get("fluss_rt"));
            setRotation(0);
            break;
        case MapTile::TYPE::RIVER_RB:
            pixmapItem->setPixmap(graphicsManager->get("fluss_rb"));
            setRotation(0);
            break;

        case MapTile::TYPE::RAIL_H:
            pixmapItem->setPixmap(graphicsManager->get("schiene_h"));
            pixmapItem->setToolTip("Schiene");
            setRotation(0);
            break;
        case MapTile::TYPE::RAIL_V:
            pixmapItem->setPixmap(graphicsManager->get("schiene_h"));
            pixmapItem->setToolTip("Schiene");
            setRotation(1);
            break;
        case MapTile::TYPE::RAIL_LT:
            pixmapItem->setPixmap(graphicsManager->get("schiene_kurve"));
            pixmapItem->setToolTip("Kurve");
            setRotation(0);
            break;
        case MapTile::TYPE::RAIL_RT:
            pixmapItem->setPixmap(graphicsManager->get("schiene_kurve"));
            pixmapItem->setToolTip("Kurve");
            setRotation(1);
            break;
        case MapTile::TYPE::RAIL_RB:
            pixmapItem->setPixmap(graphicsManager->get("schiene_kurve"));
            pixmapItem->setToolTip("Kurve");
            setRotation(2);
            break;
        case MapTile::TYPE::RAIL_LB:
            pixmapItem->setPixmap(graphicsManager->get("schiene_kurve"));
            pixmapItem->setToolTip("Kurve");
            setRotation(3);
            break;
        case MapTile::TYPE::WATER:
            pixmapItem->setPixmap(graphicsManager->get("water"));
            pixmapItem->setToolTip("Meer");
            break;
        case MapTile::TYPE::STATION_H:
            pixmapItem->setPixmap(graphicsManager->get("bahnhof"));
            pixmapItem->setToolTip("Bahnhof");
            setRotation(1);
            break;
        case MapTile::TYPE::STATION_V:
            pixmapItem->setPixmap(graphicsManager->get("bahnhof"));
            pixmapItem->setToolTip("Bahnhof");
            break;
        case MapTile::TYPE::DEPOT_H:
            pixmapItem->setPixmap(graphicsManager->get("depot"));
            pixmapItem->setToolTip("Depot");
            break;
        case MapTile::TYPE::DEPOT_V:
            pixmapItem->setPixmap(graphicsManager->get("depot"));
            pixmapItem->setToolTip("Depot");
            setRotation(1);
            break;
        case MapTile::TYPE::TERMINAL_H:
            pixmapItem->setPixmap(graphicsManager->get("terminal"));
            pixmapItem->setToolTip("Terminal");
            break;
        case MapTile::TYPE::TERMINAL_V:
            pixmapItem->setPixmap(graphicsManager->get("terminal"));
            pixmapItem->setToolTip("Terminal");
            setRotation(1);
            break;
        case MapTile::TYPE::BRIDGE_H:
            pixmapItem->setPixmap(graphicsManager->get("bruecke"));
            pixmapItem->setToolTip("Brücke");
            break;
        case MapTile::TYPE::BRIDGE_V:
            pixmapItem->setPixmap(graphicsManager->get("bruecke"));
            pixmapItem->setToolTip("Brücke");
            setRotation(1);
            break;

        case MapTile::CORN:
            pixmapItem->setPixmap(graphicsManager->get("getreide"));
            pixmapItem->setToolTip("getreide");
            break;
        case MapTile::COAL:
            pixmapItem->setPixmap(graphicsManager->get("kohlemine"));
            pixmapItem->setToolTip("Kohlemine");
            break;
        case MapTile::WOOD:
            pixmapItem->setPixmap(graphicsManager->get("holz"));
            pixmapItem->setToolTip("holz");
            break;
        case MapTile::FOOD:
            pixmapItem->setPixmap(graphicsManager->get("essen"));
            pixmapItem->setToolTip("essen");
            break;
        case MapTile::LIVESTOCK:
            pixmapItem->setPixmap(graphicsManager->get("vieh"));
            pixmapItem->setToolTip("vieh");
            break;
        case MapTile::GOODS:
            pixmapItem->setPixmap(graphicsManager->get("gueter"));
            pixmapItem->setToolTip("gueter");
            break;
        case MapTile::PETROLEUM:
            pixmapItem->setPixmap(graphicsManager->get("petrolium"));
            pixmapItem->setToolTip("petrolium");
            break;
        case MapTile::PAPER:
            pixmapItem->setPixmap(graphicsManager->get("papier"));
            pixmapItem->setToolTip("papier");
            break;
        case MapTile::STEEL:
            pixmapItem->setPixmap(graphicsManager->get("stahl"));
            pixmapItem->setToolTip("stahl");
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
 * @brief MapTile::getRotationDeg Liefert die aktuelle Rotation in Grad
 * @return 0,90,180 oder 270
 */
int MapTile::getRotationDeg()
{
    switch(currentRotation){
        case 0:
            return 0;
        case 1:
            return 90;
        case 2:
            return 180;
        default:
            return 270;
    }
}



/**
 * @brief MapTile::isRiver Checkt ob die Kachel ein Fluss ist.
 * @return Ob die Kachel ein Fluss ist.
 */
bool MapTile::isRiver(){
    return type==MapTile::TYPE::RIVER_H
            || type==MapTile::TYPE::RIVER_V
            || type==MapTile::TYPE::RIVER_LB
            || type==MapTile::TYPE::RIVER_LT
            || type==MapTile::TYPE::RIVER_RB
            || type==MapTile::TYPE::RIVER_RT;
}

/**
 * @brief MapTile::isRail Checkt ob die Kachel eine Schiene ist.
 * @return Ob die Kachel eine Schiene ist.
 */
bool MapTile::isRail()
{
    return type==MapTile::RAIL_H
            || type==MapTile::RAIL_V
            || type==MapTile::RAIL_LB
            || type==MapTile::RAIL_LT
            || type==MapTile::RAIL_RB
            || type==MapTile::RAIL_RT;
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

/**
 * @brief MapTile::isTrainStation Prüft ob die Kachel ein Bahnhof ist.
 * @return true wenn Bahnhof.
 */
bool MapTile::isTrainStation()
{
    return type == DEPOT_H || type == DEPOT_V || type == STATION_H || type == STATION_V || type == TERMINAL_H || type == TERMINAL_V;
}








