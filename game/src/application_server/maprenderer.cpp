#include "maprenderer.h"

#include <QPainter>
#include <QDebug>

/**
 * @brief MapRenderer::MapRenderer Erzeugt einen neuen MapRenderer
 * @param pGraphicsManager Der GraphicsManager
 * @param pDataModel Das Datenmodell.
 */
MapRenderer::MapRenderer(GraphicsManager * pGraphicsManager, DataModel * pDataModel):
    graphicsManager{pGraphicsManager}, dataModel{pDataModel}
{
    for(int x = 0; x<300; x++){
        for(int y = 0; y<300; y++){
            data[x][y].attachGraphicsManager(graphicsManager);
            data[x][y].setType(MapTile::GRASS);
            data[x][y].setPosition(x*64,y*64);
            data[x][y].setRotation(rand()%4);
        }
    }

    QWidget::setMouseTracking(true);

    showHighlight = true;

    demo();
}

/**
 * @brief MapRenderer::paintEvent Rendert die Spielansicht.
 * @param event Ein QPaintEvent.
 */
void MapRenderer::paintEvent(QPaintEvent *event)
{
    rendering = true;
    QPainter painter(this);

    Point minPos = getMinPos().toTile();
    Point maxPos = getMaxPos().toTile();
    for(int x = minPos.getX(); x<maxPos.getX(); x++){
        for(int y = minPos.getY(); y<maxPos.getY(); y++){
            if(x > 0 && y > 0 && x < 300 && y < 300){
                if(data[x][y].getRotationDeg()>0){
                    painter.save();
                    painter.translate(x*(64*scale)-offset.getX()+32,y*(64*scale)-offset.getY()+32);
                    painter.rotate(data[x][y].getRotationDeg());
                    painter.drawImage(-32,-32, data[x][y].getPixmapItem()->pixmap().toImage().scaled(64*scale, 64*scale));;
                    painter.restore();
                }else{
                    //painter.drawRect(x*(64*scale)-offset.getX(),y*(64*scale)-offset.getY(), 64,64);
                    painter.drawImage(x*(64*scale)-offset.getX(),y*(64*scale)-offset.getY(), data[x][y].getPixmapItem()->pixmap().toImage().scaled(64*scale, 64*scale));;
                }
            }
         }
    }

    for(AnimationMovement * anim : movementAnimations){
        anim->move();
        Point pos = anim->getEntity()->getPosition();
        pos.set((pos.getX() - offset.getX()), (pos.getY() - offset.getY()));
        if(anim->getEntity()->rotation>0){
            painter.save();
            painter.translate(pos.getX()+32, pos.getY()+32);
            painter.rotate(anim->getEntity()->rotation);
            painter.drawImage(-32,-32, *anim->getEntity()->getImage());
            painter.restore();
        }else{
            painter.drawImage(pos.getX(), pos.getY(), *anim->getEntity()->getImage());
        }
    }

    if(showHighlight){
        Point pos = toScreenPosition(activeTile.getX(), activeTile.getY());
        painter.drawRect(pos.getX(), pos.getY(), 64,64);
    }

    QWidget::paintEvent(event);
    rendering = false;
}

/**
 * @brief MapRenderer::mapPosition Wandelt eine Position im Fenster in eine Kachelkoordinate um.
 * @param px Die X-Koordinate im Fenster.
 * @param py Die Y-Koordinate im Fenster.
 * @return Der Punkt.
 */
Point MapRenderer::mapPosition(int px, int py){
    return Point(((offset.getX() + px) / 64), ((offset.getY() + py) / 64));
}

/**
 * @brief MapRenderer::toScreenPosition Wandelt einen Kachelindex in eine Koordinate auf dem Bildschirm um.
 * @return Der Punkt.
 */
Point MapRenderer::toScreenPosition(int px, int py)
{
    return Point((px*64 - offset.getX()), (py*64 - offset.getY()));
}


void MapRenderer::mousePressEvent(QMouseEvent *event)
{
    mouseDown = true;
    dragPosition.set(event->x(), event->y());
    dragOrigin.set(event->x(), event->y());
}

void MapRenderer::mouseReleaseEvent(QMouseEvent *event)
{
    mouseDown = false;
    if(event->x() - dragOrigin.getX() == 0 && event->y() - dragOrigin.getY() == 0){
        qDebug() << "lc";
        Point pos = mapPosition(event->x(), event->y());
        emit leftclick();
    }
}

void MapRenderer::mouseMoveEvent(QMouseEvent *event)
{
    if(mouseDown){
        offset.move(dragPosition.getX() - event->x(), dragPosition.getY() - event->y());
        dragPosition.set(event->x(), event->y());
    }else{
        activeTile = mapPosition(event->x(), event->y());
        dataModel->updateCoordinates(activeTile.getX(), activeTile.getY());
    }
}

void MapRenderer::wheelEvent(QWheelEvent *event)
{
    /**
    if(event->delta()>0){
        scale-=0.1;
    }else{
        scale+=0.1;
    }
    */
    repaint();
}

void MapRenderer::tick()
{
    if(!rendering)
        update();
}

/**
 * @brief MapRenderer::demo Zeigt eine Demo-Visualisierung.
 */
void MapRenderer::demo()
{
    for(int x = 0; x<300; x++){
        for(int y = 0; y<300; y++){
            int random = std::rand()%100;
            if(random>80){
                data[x][y].setType(MapTile::TYPE::FORREST);
            }else{
                data[x][y].setType(MapTile::TYPE::GRASS);
            }
            data[x][y].setRotation(std::rand()%4);
        }
    }

    for(int townIndex = 0; townIndex<300; townIndex++){
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

        int posX = std::rand()%300;
        int posY = std::rand()%300;
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
            }else if(posX>=300){
                posX=300-1;
            }
            if(posY<0){
                posY=0;
            }else if(posY>=300){
                posY=300-1;
            }
            while(data[posX][posY].getType()==MapTile::CITY && posX<300-1){
                posX++;
            }
        }
    }

    //Flussgenerierung hier drunter. Bsp: data[1][2].setType(MapTile::RIVER_H) setzt die Kachel bei Position 1,2 auf einen horizontalen Fluss

    int riverCount = std::rand()%(300/6)+20;

    for(int riverIndex = 0; riverIndex<riverCount; riverIndex++){
        int posX = std::rand()%300;
        int posY = std::rand()%300;
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
        }while(posX>0 && posY>0 && posX<300-1 && posY<300-1 && data[posX+vx][posY+vy].isRiver());
    }

    for(int x = 3; x<=5; x++){
        data[x][5].setType(MapTile::RAIL_H);
    }
    for(int y = 6; y<=9; y++){
        data[4][y].setType(MapTile::RAIL_V);
    }
    animateMovement(QImage(":/images/train_top.png"), "3:5;5:5", 0.5);
    animateMovement(QImage(":/images/train_top.png"), "4:6;4:9");

    for(int x = 7; x<=9; x++){
        data[x][5].setType(MapTile::RAIL_H);
        data[x][7].setType(MapTile::RAIL_H);
        data[x][9].setType(MapTile::RAIL_H);
    }
    for(int y = 5; y<=9; y++){
        data[7][y].setType(MapTile::RAIL_V);
    }
    data[7][5].setType(MapTile::RAIL_RB);
    data[7][9].setType(MapTile::RAIL_RT);
    animateMovement(QImage(":/images/train_top.png"), "9:5;7:5;7:9;9:9;7:9;7:5", 10);
    animateMovement(QImage(":/images/train_top.png"), "8:7;9:7");

    for(int x = 11; x<=13; x++){
        data[x][5].setType(MapTile::RAIL_H);
    }
    data[11][5].setType(MapTile::RAIL_RB);
    data[11][6].setType(MapTile::RAIL_V);
    data[11][7].setType(MapTile::RAIL_RT);
    data[12][7].setType(MapTile::RAIL_H);
    data[13][7].setType(MapTile::RAIL_LB);
    data[13][8].setType(MapTile::RAIL_V);
    data[13][9].setType(MapTile::RAIL_LT);
    data[11][9].setType(MapTile::RAIL_H);
    data[12][9].setType(MapTile::RAIL_H);
    animateMovement(QImage(":/images/train_top.png"), "13:5;11:5;11:7;13:7;13:9;11:9;13:9;13:7;11:7;11:5", 2);

    for(int x = 15; x<=17; x++){
        data[x][5].setType(MapTile::RAIL_H);
    }
    for(int y = 6; y<=9; y++){
        data[16][y].setType(MapTile::RAIL_V);
    }
    animateMovement(QImage(":/images/train_top.png"), "15:5;17:5");
    animateMovement(QImage(":/images/train_top.png"), "16:6;16:9", 4);


    //for(int i = 0; i<100; i++){animateMovement(QImage(":/images/thomasAndFriends.png"), QString::number(random()%10)+":"+QString::number(random()%10) + ";" + QString::number(random()%50) + ":" + QString::number(random()%50), random()%2+1);}
}


/**
 * @brief MapRenderer::getMinPos Gibt die minimale Position des Viewports zurück.
 * @return Ein Point.
 */
Point MapRenderer::getMinPos(){
    return offset;
}

/**
 * @brief MapRenderer::getMinPos Gibt die maximale Position des Viewports zurück.
 * @return Ein Point.
 */
Point MapRenderer::getMaxPos(){
    return offset.add(this->width()+64, this->height()+64);
}

void MapRenderer::animateMovement(QImage img, QString path)
{
    AnimationMovement * anim = new AnimationMovement(new AnimationEntity(new QImage(img)), path);
    movementAnimations.push_back(anim);
}

void MapRenderer::animateMovement(QImage img, QString path, double speed)
{
    AnimationMovement * anim = new AnimationMovement(new AnimationEntity(new QImage(img)), path);
    anim->setSpeed(speed);
    movementAnimations.push_back(anim);
}

/**
 * @brief MapRenderer::onTileChange Wird aufgerufen wenn sich eine Kachel ändert.
 * @param px Der X-Index
 * @param py Der Y-Index
 * @param type Der neue Typ als Zahl (Index in MapTile::TYPE)
 */
void MapRenderer::onTileChange(int px, int py, int type)
{
    data[px][py].setType(MapTile::TYPE(type));
}

/**
 * @brief MapRenderer::enableHighlight Wird aufgerufen wenn der Highlighter aktiviert wird.
 * @param status Der Status (an/aus)
 */
void MapRenderer::enableHighlight(bool status)
{
    showHighlight = status;
}


