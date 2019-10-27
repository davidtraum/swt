#include "scene.h"
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

    for(int townIndex = 0; townIndex<MAP_SIZE; townIndex++){
        int townSize = std::rand()%20;
        City * city = new City();
        city->setSize(townSize);
        city->setName("Stadt " + std::to_string(townIndex));
        int posX = std::rand()%MAP_SIZE;
        int posY = std::rand()%MAP_SIZE;
        int minX = posX;
        int minY = posY;
        int maxX = posX;
        int maxY = posY;
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
            if(posX<minX){
                minX=posX;
            }else if(posX>maxX){
                maxX=posX;
            }
            if(posY<minY){
                minY=posY;
            }else if(posY>maxY){
                maxY=posX;
            }
        }
    }

    for(int riverIndex = 0; riverIndex<MAP_SIZE/100; riverIndex++){
        int posX = (std::rand()%MAP_SIZE);
        int posY = (std::rand()%MAP_SIZE);
        int vx = 1;
        int vy = 0;
        int dir = 1;
        do{
            if(vx==1 && vy==0){
                data[posX][posY].setType(MapTile::TYPE::RIVER_H); //Horizontales Stück
            }else if(vx==0 && vy==1){
                data[posX][posY].setType(MapTile::TYPE::RIVER_V); //Vertikales Stück
            }else if(vx==1 && vy==2){
                if(dir==1){
                    data[posX][posY].setType(MapTile::TYPE::RIVER_LB); //Kurve nach unten
                }else{
                    data[posX][posY].setType(MapTile::TYPE::RIVER_RB);
                }
                vx=0;
                vy=1;
            }else if(vx==2 && vy==1){
                if(dir==1){
                    data[posX][posY].setType(MapTile::TYPE::RIVER_RT); //Kurve nach rechts
                }else{
                    data[posX][posY].setType(MapTile::TYPE::RIVER_LT);
                }
                vx=1;
                vy=0;
            }
            posX+=(vx*dir);
            posY+=(vy*dir);
            if(std::rand()%100 > 90){
                if(vx==0){
                    vx=2;
                    vy=1; //Kurve in die Horizontale
                }else{
                    vx=1; //Kurve in die Vertikale
                    vy=2;
                }
            }else if(std::rand()%100 > 90){
                dir*=-1; //Richtung wird umgekehrt
            }
        }while(posX < MAP_SIZE && posX>=0 && posY<MAP_SIZE && posY>=0);
    }

    //Sonderfunktionen werden hinzugefügt
    QGraphicsScene::addItem(highlighter);
    QGraphicsScene::addItem(radiusHighlighter);
    QGraphicsScene::addItem(textHint);
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
        qDebug() << "City detected";
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
