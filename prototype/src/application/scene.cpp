#include "scene.h"
#include <QDebug>

Scene::Scene()
{
    QGraphicsScene::setSceneRect(0,0, MAP_SIZE*TILE_SIZE, MAP_SIZE*TILE_SIZE);
}

/**
 * @brief Scene::generateWorld Diese Methode generiert eine neue Welt.
 */
void Scene::generateWorld(){
    QGraphicsScene::clear();

    //Hier wird die Landschaft generiert.
    MapTile data[Scene::MAP_SIZE][Scene::MAP_SIZE]{};
    for(int x = 0; x<MAP_SIZE; x++){
        for(int y = 0; y<MAP_SIZE; y++){
            int random = std::rand()%100;
            if(random>95){
                data[x][y].setup(MapTile::TYPE::CITY, x*TILE_SIZE, y*TILE_SIZE);
            }else if(random>60){
                data[x][y].setup(MapTile::TYPE::FORREST, x*TILE_SIZE, y*TILE_SIZE);
            }else{
                data[x][y].setup(MapTile::TYPE::GRASS, x*TILE_SIZE, y*TILE_SIZE);
            }
            QGraphicsScene::addItem(data[x][y].getPixmapItem());
        }
    }

    //Hier werden die Flüsse generiert
    for(int riverIndex = 0; riverIndex<5; riverIndex++){
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
}
