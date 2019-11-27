#include "scene.h"
#include "maptile.h"
#include <QDebug>
#include <QPen>
#include <QPainter>

/**
 * @brief Scene::Scene Konstruktor
 */
Scene::Scene(GraphicsManager * pGraphicsManager, DataModel * pDataModel)
{
    graphicsManager = pGraphicsManager;
    dataModel = pDataModel;
    QGraphicsScene::setSceneRect(0,0, MAP_SIZE*TILE_SIZE, MAP_SIZE*TILE_SIZE);
    activeTile = nullptr;

    highlighter = new Highlighter();
    QGraphicsScene::addItem(highlighter);

    dataModel->secondPlayer = new Player();
    dataModel->secondPlayer->highlighter->setColor(Qt::lightGray);
    QGraphicsScene::addItem(dataModel->secondPlayer->highlighter);

    textHint = new QGraphicsTextItem();
    textHint->setDefaultTextColor(QColor(Qt::white));
    textHint->setScale(4);
    textHint->setZValue(3);

    for(int x = 0; x<MAP_SIZE; x++){
        for(int y = 0; y<MAP_SIZE; y++){
            data[x][y].attachGraphicsManager(graphicsManager);
            data[x][y].setType(MapTile::GRASS);
            data[x][y].setPosition(x*64,y*64);
            data[x][y].setRotation(std::rand()%4);
            QGraphicsScene::addItem(data[x][y].getPixmapItem());
        }
    }
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

    int riverCount = std::rand()%(MAP_SIZE/6)+5;
    qDebug() << "[WELT] Es werden " << riverCount << " Flüsse generiert.";

    for(int riverIndex = 0; riverIndex<riverCount; riverIndex++){
        int posX = std::rand()%MAP_SIZE;
        int posY = std::rand()%MAP_SIZE;
        int vx = 1;
        int vy = 0;
        int sinceCurve = 0;
        MapTile::TYPE type = MapTile::RIVER_H;
        do{
            data[posX][posY].setType(type);
            posX+=vx;
            posY+=vy;
            sinceCurve++;
            if(sinceCurve>(std::rand()%5)+2){
                if(std::rand()%10>5){
                    switch(vy){
                        case -1:
                            vy = 0;
                            vx = 1;
                            type = MapTile::RIVER_RB;
                            break;
                        case 0:
                            if(vx==-1){
                                type = MapTile::RIVER_RT;
                            }else{
                                type = MapTile::RIVER_LT;
                            }
                            vy = -1;
                            vx = 0;
                            break;
                        case 1:
                            vy = 0;
                            vx = -1;
                            type = MapTile::RIVER_LT;
                            break;
                    }
                }else{
                    switch(vx){
                        case -1:
                            vy = 1;
                            vx = 0;
                            type = MapTile::RIVER_RB;
                            break;
                        case 0:
                            if(vy==1){
                                type = MapTile::RIVER_LT;
                            }else{
                                type = MapTile::RIVER_LB;
                            }
                            vy = 0;
                            vx = -1;
                            break;
                        case 1:
                            vy = -1;
                            vx = 0;
                            type = MapTile::RIVER_LT;
                            break;
                    }
                }
                sinceCurve=0;
            }else{
                if(vy==0){
                    type = MapTile::RIVER_H;
                }else{
                    type = MapTile::RIVER_V;
                }
            }
        }while(posX>0 && posY>0 && posX<MAP_SIZE-1 && posY<MAP_SIZE-1 && data[posX+vx][posY+vy].isRiver());
    }

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
    if(dataModel->getMode() != DataModel::DEFAULT){
        if(!highlighter->isVisible())highlighter->setVisible(true);
        highlighter->setPos(pItem->pos());
        switch(dataModel->getMode()){
            case DataModel::RAIL_PLACEMENT:
                if(data[activeTile->getX()-1][activeTile->getY()].isRail() ||
                        data[activeTile->getX()+1][activeTile->getY()].isRail() ||
                        data[activeTile->getX()][activeTile->getY()+1].isRail() ||
                        data[activeTile->getX()][activeTile->getY()-1].isRail()){
                    highlighter->setColor(Qt::green);
                }else{
                    highlighter->setColor(Qt::white);
                }
        }
    }else{
        highlighter->setVisible(false);
    }
    if(activeTile->getType()==MapTile::CITY && false){
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
 * @brief Scene::getTileAt Liefert ein MapTile anhand der Pixel-Koordinaten oder der Indizes.
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



/**
 * @brief Scene::setTileAt Setzt ein MapTile anhand der Pixel-Koordinaten oder der  Indezes.
 * @param posX
 * @param posY
 * @param isPixelCoordinate
 */
void Scene::setTileAt(int pX,int pY, int pType, int pRotation){
    data[pX][pY].setType(static_cast<MapTile::TYPE>(pType));
    data[pX][pY].setRotation(pRotation);
    emit tileUpdate(pX,pY,pType,pRotation);
}

/**
 * @brief Scene::tileChanged Meldet das sich ein MapTile geändert hat.
 * @param pX Die X-Koordinate.
 * @param pY Die Y-Koordinate.
 */
void Scene::tileChanged(int pX, int pY){
    emit tileUpdate(pX, pY, int(data[pX][pY].getType()), data[pX][pY].getRotation());
}

/**
 * @brief Scene::tick Asynchrone Tickfunktion. Wird alle 20ms aufgerufen.
 */
void Scene::tick()
{

}

/**
 * @brief Scene::onSetTile Ändert ein MapTile ohne ein Signal an den Server. Notwendig zum Empfangen von Änderungen.
 * @param pX Die X-Koordinate.
 * @param pY Die Y-Koordinate.
 * @param pType Der Typ.
 * @param pRotation Die Rotation.
 */
void Scene::onSetTile(int pX, int pY, int pType, int pRotation){
    data[pX][pY].setType(static_cast<MapTile::TYPE>(pType));
    if(pRotation>0){
        qDebug() << "Has rotation " << pRotation;
    }
    data[pX][pY].setRotation(pRotation);
}

/**
 * @brief Scene::updatePlayerPosition Slot zum Updaten eines Spielers.
 */
void Scene::updatePlayerPosition(int pX, int pY)
{
    dataModel->secondPlayer->setPosition(pX,pY);
    emit dataModel->viewChange();
}
