#include "maprenderer.h"

#include <QPainter>
#include <QDebug>
#include <ctime>
#include <QHBoxLayout>

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
            data[x][y].setPosition(x*tileSize,y*tileSize);
            data[x][y].setRotation(rand()%4);
        }
    }

    data[150][150].setType(MapTile::DEPOT_H);

    QWidget::setMouseTracking(true);
    QWidget::setFocusPolicy(Qt::FocusPolicy::StrongFocus);
    QWidget::setFocus();

    showHighlight = true;
    codeCount = 0;
}

/**
 * @brief MapRenderer::paintEvent Rendert die Spielansicht.
 * @param event Ein QPaintEvent.
 */
void MapRenderer::paintEvent(QPaintEvent *event)
{
    rendering = true;
    long beforeTime = clock();
    QPainter painter(this);

    if(moveStepsLeft>0){
        offset.move(int(vx),int(vy));
        dataModel->updateCoordinates(offset.getX()/tileSize, offset.getY()/tileSize);
        moveStepsLeft--;
    }

    Point minPos = getMinPos().toTile();
    Point maxPos = getMaxPos().toTile();
    for(int x = minPos.getX(); x<maxPos.getX(); x++){
        for(int y = minPos.getY(); y<maxPos.getY(); y++){
            if(x > 0 && y > 0 && x < 300 && y < 300){
                if(data[x][y].getRotationDeg()>0){
                    painter.save();
                    painter.translate(x*(tileSize)-offset.getX()+halfSize,y*(tileSize)-offset.getY()+halfSize);
                    painter.rotate(data[x][y].getRotationDeg());
                    painter.drawImage(-halfSize,-halfSize, data[x][y].getPixmapItem()->pixmap().toImage().scaled(tileSize*scale, tileSize*scale));
                    painter.restore();
                }else{
                    //painter.drawRect(x*(tileSize*scale)-offset.getX(),y*(tileSize*scale)-offset.getY(), tileSize,tileSize);
                    painter.drawImage(x*(tileSize)-offset.getX(),y*(tileSize)-offset.getY(), data[x][y].getPixmapItem()->pixmap().toImage().scaled(tileSize*scale, tileSize*scale));
                }
            }
         }
    }

    for(AnimationMovement * anim : movementAnimations){
        if(anim->move()){
            movementAnimations.removeOne(anim);
            delete anim;
        }else{
            Point pos = anim->getEntity()->getPosition();
            pos.set((pos.getX() - offset.getX()), (pos.getY() - offset.getY()));
            if(anim->getEntity()->rotation>0){
                painter.save();
                painter.translate(pos.getX()+halfSize, pos.getY()+halfSize);
                painter.rotate(anim->getEntity()->rotation);
                painter.drawImage(-halfSize,-halfSize, *anim->getEntity()->getImage());
                painter.restore();
            }else{
                painter.drawImage(pos.getX(), pos.getY(), *anim->getEntity()->getImage());
            }
        }
    }

    if(showHighlight){
        Point pos = toScreenPosition(activeTile.getX(), activeTile.getY());
        painter.drawRect(pos.getX(), pos.getY(), tileSize,tileSize);
    }


    QWidget::paintEvent(event);
    renderTime = clock() - beforeTime;

    if(showExpertDetails){
        painter.drawText(10,20, "Render Details (F3)");
        painter.drawText(10,40,"Render Time: " + QString::number(renderTime/1000) + "ms");
        painter.drawText(10, 55, "Constant FPS: " + QString::number(fps));
        painter.drawText(10, 70, "Possible FPS: " + QString::number(1000000/renderTime));
        painter.drawText(10, 85, "Index Position: " + QString::number(activeTile.getX()) + "/" + QString::number(activeTile.getY()));
        painter.drawText(10, 100, "Tiles drawn: " + QString::number((maxPos.getX() - minPos.getY()) * (maxPos.getY() - minPos.getY())));
        painter.drawText(10, 115, "Active animations: " + QString::number(movementAnimations.length()));
    }

    frameCount++;
    if((time(nullptr) - lastFpsTake)>=1){
        lastFpsTake = time(nullptr);
        fps = frameCount;
        frameCount = 0;
    }
    rendering = false;
}

/**
 * @brief MapRenderer::mapPosition Wandelt eine Position im Fenster in eine Kachelkoordinate um.
 * @param px Die X-Koordinate im Fenster.
 * @param py Die Y-Koordinate im Fenster.
 * @return Der Punkt.
 */
Point MapRenderer::mapPosition(int px, int py){
    return Point(((offset.getX() + px) / tileSize), ((offset.getY() + py) / tileSize));
}

/**
 * @brief MapRenderer::toScreenPosition Wandelt einen Kachelindex in eine Koordinate auf dem Bildschirm um.
 * @return Der Punkt.
 */
Point MapRenderer::toScreenPosition(int px, int py)
{
    return Point((px*tileSize - offset.getX()), (py*tileSize - offset.getY()));
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
        emit tileClick(activeTile.getX(), activeTile.getY(), data[activeTile.getX()][activeTile.getY()].getType());
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
    if(event->delta()>0){
        tileSize++;
    }else{
        tileSize--;
    }
}

void MapRenderer::keyReleaseEvent(QKeyEvent *event)
{
    switch(event->key()){
        case Qt::Key_F3:
            showExpertDetails = !showExpertDetails;
            break;
        case Qt::Key_F11:
            dataModel->toggleFullscreen();
            break;
        case Qt::Key_F6:
            ea1c++;
            if(ea1c>10){
                demo();
            }
            break;
        case Qt::Key_Left:
            if (codeCount == 4 || codeCount == 6)
                codeCount++;
            else
                codeCount = 0;
            break;
        case Qt::Key_Right:
            if (codeCount == 5 || codeCount == 7)
                codeCount++;
            else
                codeCount = 0;
            break;
        case Qt::Key_Up:
            if (codeCount == 0 || codeCount == 1)
                codeCount++;
            else
                codeCount = 0;
            break;
        case Qt::Key_Down:
            if (codeCount == 2 || codeCount == 3)
                codeCount++;
            else
                codeCount = 0;
            break;
        case Qt::Key_B:
            if (codeCount == 8)
                codeCount++;
            else
                codeCount = 0;
            break;
        case Qt::Key_A:
            if (codeCount == 9)
                codeCount++;
            else
                codeCount = 0;
            break;
        default:
            codeCount = 0;
        break;
      }

    //qDebug() << "codeCount " << QString::number(codeCount);

    //Hier gibt es nichts zu sehen:
    if (codeCount == 10) {
        qDebug("KONAMI CODE");
        QWidget* box = new QWidget();
        box->setWindowModality(Qt::ApplicationModal);
        box->setWindowTitle("Thomas And Friends");

        QHBoxLayout* layout = new QHBoxLayout();
        box->setLayout(layout);

        QPixmap p(":/images/thomasAndFriends.png");
        QLabel * image = new QLabel(this);
        image->setPixmap(p.scaled(800, 800,Qt::KeepAspectRatio, Qt::FastTransformation));

        layout->addWidget(image);
        image->show();
        box->show();
    }
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
    //animateMovement(QImage(":/images/train_top.png"), "4:6;4:9");

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
    //animateMovement(QImage(":/images/train_top.png"), "8:7;9:7");

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
    //animateMovement(QImage(":/images/train_top.png"), "15:5;17:5");
    animateMovement(QImage(":/images/train_top.png"), "16:6;16:9", 4);


    emit dataModel->viewChange();

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
    return offset.add(this->width()+tileSize, this->height()+tileSize);
}

/**
 * @brief MapRenderer::getTileCenter Liefert die Koordinate der zentralen Kachel zurück.
 * @return Ein Punkt.
 */
Point MapRenderer::getTileCenter()
{
    return Point(int((offset.getX()+this->width()*0.5) / tileSize), int((offset.getY()+this->height()) / tileSize));
}

/**
 * @brief MapRenderer::animateMovementToTilePosition Führt eine Bewegungsanimation zu einer Kachelkoordinate durch.
 */
void MapRenderer::animateMovementToTilePosition(int px, int py)
{
    Point center(offset.getX() / tileSize, offset.getY() / tileSize);
    vx = px*tileSize-center.getX()*tileSize;
    vy = py*tileSize-center.getY()*tileSize;
    vx/=20;
    vy/=20;
    moveStepsLeft=20;
}

/**
 * @brief MapRenderer::setViewportTilePosition Verschiebt den Viewport zu einer Tile-Koordinate.
 * @param px Die X-Koordinate.
 * @param py Die Y-Koordinate.
 */
void MapRenderer::setViewportTilePosition(int px, int py)
{
    offset.set(px*tileSize, py*tileSize);
    dataModel->updateCoordinates(px,py);
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


