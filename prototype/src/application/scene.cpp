#include "scene.h"
#include "maptile.h"
#include <QDebug>
#include <QPen>
#include <QPainter>


/**
 * @brief Scene::Scene Konstruktor
 */
Scene::Scene()
{
    QGraphicsScene::setSceneRect(0,0, MAP_SIZE*TILE_SIZE, MAP_SIZE*TILE_SIZE);
    activeTile = nullptr;

    highlighter = new QGraphicsRectItem();
    highlighter->setRect(0,0,TILE_SIZE,TILE_SIZE);
    QPen * outline = new QPen();
    outline->setColor(QColor(Qt::white));
    outline->setWidth(2);
    highlighter->setPen(*outline);
    highlighter->setZValue(2);

    radiusHighlighter = new QGraphicsEllipseItem();
    outline->setWidth(6);
    outline->setColor(QColor(Qt::yellow));
    radiusHighlighter->setPen(*outline);
    radiusHighlighter->setZValue(1);
    showRadius = false;

    textHint = new QGraphicsTextItem();
    textHint->setDefaultTextColor(QColor(Qt::white));
    textHint->setScale(4);
    textHint->setZValue(3);
}

/**
 * @brief Scene::generateWorld Diese Methode generiert eine neue Welt.
 */
void Scene::generateWorld(){
    QGraphicsScene::clear();

    //Hier wird die Landschaft generiert.
    qDebug() << "[WELT] Landschaft wird generiert...";
    for(int x = 0; x<MAP_SIZE; x++){
        for(int y = 0; y<MAP_SIZE; y++){
            int random = std::rand()%100;
            data[x][y].setPosition(x*TILE_SIZE, y*TILE_SIZE);
            if(random>80){
                data[x][y].setType(MapTile::TYPE::FORREST);
            }else{
                data[x][y].setType(MapTile::TYPE::GRASS);
            }
            data[x][y].setRotation(std::rand()%4); //Zufällige Rotation
            data[x][y].getPixmapItem()->setZValue(0);
            QGraphicsScene::addItem(data[x][y].getPixmapItem());
        }
    }

    qDebug() << "[WELT] Es werden " << MAP_SIZE << " Städte generiert...";
    for(int townIndex = 0; townIndex<MAP_SIZE; townIndex++){
        int townSize = (std::rand()%20)+1;
        City * city = new City();
        city->setSize(townSize);
        if(townSize<4){
              city->setName("Dorf #" + std::to_string(townIndex));
        }else if(townSize<10){
            city->setName("Stadt #" + std::to_string(townIndex));
        }else if(townSize<15){
            city->setName("Großstadt #" + std::to_string(townIndex));
        }else{
            city->setName("Metropole #" + std::to_string(townIndex));
        }

        int posX = std::rand()%MAP_SIZE;
        int posY = std::rand()%MAP_SIZE;
        for(int i = 0; i<townSize; i++){
            if(i==int(townSize/2)){
                city->setCenter(posX,posY);
            }
            data[posX][posY].setType(MapTile::TYPE::CITY);
            data[posX][posY].setCity(city);
            data[posX][posY].setRotation(std::rand()%4);
            posX+=(1-(std::rand()%3));
            posY+=(1-(std::rand()%3));
            if(posX<0){
                posX=0;
            }else if(posX>=MAP_SIZE){
                posX=MAP_SIZE-1;
            }
            if(posY<0){
                posY=0;
            }else if(posY>=MAP_SIZE){
                posY=MAP_SIZE-1;
            }
            while(data[posX][posY].getType()==MapTile::CITY && posX<MAP_SIZE-1){
                posX++;
            }
        }
    }

    //Flussgenerierung hier drunter. Bsp: data[1][2].setType(MapTile::RIVER_H) setzt die Kachel bei Position 1,2 auf einen horizontalen Fluss


    //Sonderfunktionen werden hinzugefügt
    QGraphicsScene::addItem(highlighter);
    QGraphicsScene::addItem(radiusHighlighter);
    QGraphicsScene::addItem(textHint);

    qDebug() << "[WELT] Generierung abgeschlossen.";
}


/**
 * @brief Scene::setActiveTile Setzt den MapTile über dem die Maus gerade ist. Wird von view aufgerufen.
 * @param pItem Ein Grafikitem zu dem die Methode den zugehörigen Maptile bestimmt.
 */
void Scene::setActiveTile(QGraphicsItem *pItem){
    if(activeTile != nullptr){
        //Alten aktiven Quadrant zurücksetzen.
    }
    activeTile = &data[int(pItem->x()/TILE_SIZE)][int(pItem->y()/TILE_SIZE)];
    highlighter->setPos(pItem->pos());
    if(activeTile->getType()==MapTile::CITY){
        City * city = activeTile->getCity();
        radiusHighlighter->setX(city->getCenterX()*TILE_SIZE+32);
        radiusHighlighter->setY(city->getCenterY()*TILE_SIZE+32);
        radiusHighlighter->setRect(-(city->getSize()*TILE_SIZE)*0.5,
                                   -(city->getSize()*TILE_SIZE)*0.5,
                                   city->getSize()*TILE_SIZE,
                                   city->getSize()*TILE_SIZE);
        radiusHighlighter->setVisible(true);
        textHint->setPos(city->getCenterX()*TILE_SIZE-textHint->boundingRect().width()*0.5, city->getCenterY()*TILE_SIZE-city->getSize()*TILE_SIZE*0.5-50);
        textHint->setPlainText(QString::fromStdString(city->getName()));
        textHint->setVisible(true);
        showRadius = true;
        highlighter->setVisible(false);
    }else if(showRadius){
        radiusHighlighter->setVisible(false);
        highlighter->setVisible(true);
        textHint->setVisible(false);
        showRadius = false;
    }
}

/**
 * @brief Scene::getTileAt Liefert ein MapTile anhand der Pixel-Koordinaten.
 * @param posX Die X-Koordinate
 * @param posY Die Y-Koordinate
 */
MapTile * Scene::getTileAt(int posX, int posY, bool isPixelCoordinate){
    if(isPixelCoordinate){
        return &data[int(posX/TILE_SIZE)][int(posY/TILE_SIZE)];
    }else{
        return &data[posX][posY];
    }
}
