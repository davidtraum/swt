#include "maprenderer.h"

#include <QPainter>
#include <QDebug>
#include <ctime>
#include <QHBoxLayout>
#include "sprite.h"

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
    data[150][151].setType(MapTile::STATION_H);
    data[150][152].setType(MapTile::TERMINAL_H);

    QWidget::setMouseTracking(true);
    QWidget::setFocusPolicy(Qt::FocusPolicy::StrongFocus);
    QWidget::setFocus();

    videoWidget = new QVideoWidget(dataModel->mainWindow);
    videoPlayer = new QMediaPlayer();
    videoPlayer->setMedia(QUrl("qrc:/video/building_bridge.mp4"));
    videoPlayer->setVideoOutput(videoWidget);
    connect(videoPlayer, &QMediaPlayer::stateChanged, this, &MapRenderer::onVideoStateChange);

    buffer = new QPixmap(this->width(), this->height());

//testSprite = new Sprite(new QImage(":/images/sprite/sheet_explosion.png"), 25,64);

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
    QPainter * painter;
    if(scale<1 || scale>1){
        delete buffer;
        buffer = new QPixmap(int(this->width()*(1/scale)), int(this->height()*(1/scale)));
        painter = new QPainter(buffer);
    }else{
        painter = new  QPainter(this);
    }


    Point minPos = getMinPos().toTile();
    Point maxPos = getMaxPos().toTile();
    dataModel->minPos = minPos;
    dataModel->maxPos = maxPos;
    for(int x = minPos.getX(); x<maxPos.getX(); x++){
        for(int y = minPos.getY(); y<maxPos.getY(); y++){
            if(x > 0 && y > 0 && x < 300 && y < 300){
                if(data[x][y].getRotationDeg()>0){
                    painter->save();
                    painter->translate(x*(tileSize)-(offset.getX())+halfSize,y*(tileSize)-offset.getY()+halfSize);
                    painter->rotate(data[x][y].getRotationDeg());
                    painter->drawImage(-halfSize,-halfSize, data[x][y].getPixmapItem()->pixmap().toImage().scaled(tileSize, tileSize));
                    painter->restore();
                }else{
                    //painter.drawRect(x*(tileSize*scale)-offset.getX(),y*(tileSize*scale)-offset.getY(), tileSize,tileSize);
                    painter->drawImage(x*(tileSize)-offset.getX(),y*(tileSize)-offset.getY(), data[x][y].getPixmapItem()->pixmap().toImage().scaled(tileSize, tileSize));
                }
            }
         }
    }

    for(AnimationMovement * anim : movementAnimations){
            Point pos = anim->getEntity()->getPosition();
            pos.set((pos.getX() - offset.getX()), (pos.getY() - offset.getY()));
            if(anim->getEntity()->rotation>0){
                painter->save();
                painter->translate(pos.getX()+halfSize, pos.getY()+halfSize);
                painter->rotate(anim->getEntity()->rotation);
                painter->drawImage(-halfSize,-halfSize, *anim->getEntity()->getImage());
                painter->restore();
            }else{
                painter->drawImage(pos.getX(), pos.getY(), *anim->getEntity()->getImage());
            }
    }
    Point pos = toScreenPosition(activeTile.getX(), activeTile.getY());
    if(showHighlight){
        painter->drawRect(pos.getX(), pos.getY(), tileSize,tileSize);
    }

            switch(data[activeTile.getX()][activeTile.getY()].getType()){
                case MapTile::DEPOT_H:
                case MapTile::DEPOT_V:
                    painter->drawRect(pos.getX()-dataModel->RADIUS_DEPOT, pos.getY()-dataModel->RADIUS_DEPOT, dataModel->RADIUS_DEPOT*2+64, dataModel->RADIUS_DEPOT*2+64);
                    break;
                case MapTile::STATION_H:
                case MapTile::STATION_V:
                    painter->drawRect(pos.getX()-dataModel->RADIUS_STATION, pos.getY()-dataModel->RADIUS_STATION, dataModel->RADIUS_STATION*2+64, dataModel->RADIUS_STATION*2+64);
                    break;
                case MapTile::TERMINAL_H:
                case MapTile::TERMINAL_V:
                    painter->drawRect(pos.getX()-dataModel->RADIUS_TERMINAL, pos.getY()-dataModel->RADIUS_TERMINAL, dataModel->RADIUS_TERMINAL*2+64, dataModel->RADIUS_TERMINAL*2+64);
                    break;
                default:
                    break;
            }


    QWidget::paintEvent(event);
    renderTime = clock() - beforeTime;

    QPainter painterReal(this);
    if(scale < 1 || scale > 1){
        painterReal.drawImage(0,0,buffer->toImage().scaled(buffer->width()*scale, buffer->height()*scale));
    }

    //painterReal.drawImage(0,0,testSprite->getImage().scaled(256,256));

    painterReal.drawText(this->width()-310,330, dataModel->getFormattedTime());
    painterReal.drawText(this->width()-310, 350, QString(QString::number(dataModel->getBalance()) + "$"));

    if(showExpertDetails){
        painterReal.drawText(10,20, "Render Details (F3)");
        painterReal.drawText(10,40,"Render Time: " + QString::number(renderTime/1000) + "ms");
        painterReal.drawText(10, 55, "Constant FPS: " + QString::number(fps));
        painterReal.drawText(10, 70, "Possible FPS: " + QString::number(1000000/renderTime));
        painterReal.drawText(10, 85, "Index Position: " + QString::number(activeTile.getX()) + "/" + QString::number(activeTile.getY()));
        painterReal.drawText(10, 100, "Tiles drawn: " + QString::number((maxPos.getX() - minPos.getY()) * (maxPos.getY() - minPos.getY())));
        painterReal.drawText(10, 115, "Active animations: " + QString::number(movementAnimations.length()));
        painterReal.drawText(10, 130, "Scale: " + QString::number(scale) + "x");
    }

    delete painter;

    frameCount++;
    if((time(nullptr) - lastFpsTake)>=1){
        lastFpsTake = time(nullptr);
        fps = frameCount;
        frameCount = 0;
        timeToRender = renderTime/1000;
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
    return Point(int((offset.getX()*(scale) + px) / tileSize*(1/scale)), int((offset.getY()*(scale) + py) / tileSize*(1/scale)));
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
    QWidget::setCursor(QCursor(Qt::PointingHandCursor));
}

void MapRenderer::mouseReleaseEvent(QMouseEvent *event)
{
    mouseDown = false;
    dataModel->getInfoWidget()->hide();
    if(event->x() - dragOrigin.getX() == 0 && event->y() - dragOrigin.getY() == 0){
        Point pos = mapPosition(event->x(), event->y());
        if(event->button() == Qt::RightButton) {
            if(data[activeTile.getX()][activeTile.getY()].isTrainStation()) {
                dataModel->getInfoWidget()->sendInfoRequest(pos.getX(), pos.getY());
                qDebug() << "sendInforRequest called";
                dataModel->getInfoWidget()->show();
            }
        }else{
            emit leftclick();
            emit tileClick(activeTile.getX(), activeTile.getY(), data[activeTile.getX()][activeTile.getY()].getType());
        }
    }
    QWidget::setCursor(QCursor());
}

void MapRenderer::mouseMoveEvent(QMouseEvent *event)
{
    if(mouseDown){
        offset.move((dragPosition.getX() - event->x()) * (1/scale), (dragPosition.getY() - event->y())*(1/scale));
        dragPosition.set(event->x(), event->y());
    }else{
        activeTile = mapPosition(event->x(), event->y());
        dataModel->updateCoordinates(activeTile.getX(), activeTile.getY());
    }
}

void MapRenderer::wheelEvent(QWheelEvent *event)
{
    if(event->delta() > 0){
        if(scale<5){
            scale += 0.1;
        }
    }else{
        if(scale > 0.6){
            scale -= 0.1;
        }
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
        case Qt::Key_F4:
            cloudAnimation();
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
    if(ticksSkipped>=framerateDelay){
        logicUpdate();
        ticksSkipped=0;
    }
    ticksSkipped++;
    if(timeSinceCloudSpawn>2000){
        spawnCloud();
        timeSinceCloudSpawn = 0;
    }
    timeSinceCloudSpawn++;
}

/**
 * @brief MapRenderer::logicUpdate Führt einen Logikschritt durch (Animationen etc.)
 */
void MapRenderer::logicUpdate()
{
    //testSprite->step();
    for(AnimationMovement * anim : movementAnimations){
        if(anim->move()){
            movementAnimations.removeOne(anim);
            delete anim;
            break;
        }else{
            Point pos = anim->getEntity()->getPosition();
            pos.set((pos.getX() - offset.getX()), (pos.getY() - offset.getY()));
        }
    }
    if(moveStepsLeft>0){
        offset.move(int(vx),int(vy));
        dataModel->updateCoordinates(offset.getX()/tileSize, offset.getY()/tileSize);
        moveStepsLeft--;
    }

    if(scaleStepsLeft>0){
        scale += scaleVector;
        scaleStepsLeft--;
    }
}

/**
 * @brief MapRenderer::renderFrame Rendert ein Frame.
 */
void MapRenderer::renderFrame()
{
    if(!rendering){
        update();
    }
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
    return offset.add(int((this->width()+(tileSize*scale))*(1/scale)), int((this->height()+tileSize*scale)*(1/scale)));
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

void MapRenderer::animateMovementTracked(QImage img, QString path, int id)
{
    AnimationMovement * anim = new AnimationMovement(new AnimationEntity(new QImage(img), id), path);
    anim->setEmitChanges(true);
    connect(anim, &AnimationMovement::reachedPoint, this, &MapRenderer::handleReachedPoint);
    movementAnimations.push_back(anim);
}

void MapRenderer::animateMovement(QImage img, QString path, double speed)
{
    AnimationMovement * anim = new AnimationMovement(new AnimationEntity(new QImage(img)), path);
    anim->setSpeed(speed);
    movementAnimations.push_back(anim);
}

/**
 * @brief MapRenderer::deleteAnimationId Löscht eine Animation anhand der Entity-Id.
 * @param pid Die Entity-Id.
 */
void MapRenderer::deleteAnimationId(int pid)
{
    for(AnimationMovement * anim : movementAnimations){
        if(anim->getEntity()->getId() == pid){
            anim->setRepeat(false);
        }
    }
}

/**
 * @brief MapRenderer::cloudAnimation Führt eine WolkpScaleen-Animation aus
 */
void MapRenderer::cloudAnimation()
{
    QImage img(":/images/cloud/cloud0.png");
    img = img.scaled(img.width()*4, img.height()*4);
    setViewportTilePosition(130,140);
    QString paths[] = {
        "140:140;100:100",
        "160:140;200:100",
        "160:160;200:200",
        "140:160;100:200"
        "130:130;90:120",
        "170:150;210:900",
        "150:150;220:210",
        "145:165;150:250"
    };
    for(QString path : paths){
        AnimationMovement * anim = new AnimationMovement(new AnimationEntity(new QImage(img)), path);
        anim->setSpeed(15);
        anim->setRepeat(false);
        movementAnimations.push_back(anim);
    }
    scale = 0.5;
    animateScale(1);
}

/**
 * @brief MapRenderer::bridgeAnimation Startet die Brückenbau-Sequenz
 */
void MapRenderer::bridgeAnimation()
{

}

/**
 * @brief MapRenderer::spawnCloud Erzeugt eine neue Wolke die über die Karte fliegt.
 */
void MapRenderer::spawnCloud()
{
    int ypos = rand() % 300;
    QImage img(":/images/cloud/cloud0_transparent.png");
    double scale = 0.5 + ((rand() % 100)*0.02);
    AnimationMovement * anim = new AnimationMovement(new AnimationEntity(new QImage(img.scaled(img.width()*scale, img.height()*scale))),
                                                     "-10:" + QString::number(ypos)  + ";300:" + QString::number(ypos));
    anim->setSpeed(2 + (0.1/scale)*8);
    anim->setRepeat(false);
    anim->setAutoRotate(false);
    movementAnimations.push_back(anim);
}

/**
 * @brief MapRenderer::animateScale Animiert die Skalierung.
 * @param pScale Die neue Skalierung.
 */
void MapRenderer::animateScale(double pScale)
{
    scaleVector = (pScale - scale) / 100;
    scaleStepsLeft = 100;
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

    if ((type == MapTile::BRIDGE_H || type == MapTile::BRIDGE_V) && DataModel::mapLoaded) {
        videoPlayer->play();
    }
}

/**
 * @brief MapRenderer::enableHighlight Wird aufgerufen wenn der Highlighter aktiviert wird.
 * @param status Der Status (an/aus)
 */
void MapRenderer::enableHighlight(bool status)
{
    showHighlight = status;
}

/**
 * @brief MapRenderer::setLogicSpeed Ändert die Geschwindigkeit der Logikschleife.
 * @param pDelay Die Verzögerung in ms zwischen den Schritten.
 */
void MapRenderer::setLogicSpeed(int pDelay)
{
    framerateDelay = pDelay;
}

/**
 * @brief MapRenderer::handleReachedPoint Wird aufgerufen, wenn eine Animation einen neuen Punkt erreicht.
 * @param px Die X-Koordinate
 * @param py Die Y-Koordinate
 * @param anim Die Animation
 */
void MapRenderer::handleReachedPoint(int px, int py, AnimationMovement * anim)
{
    if(data[px][py].isTrainStation()){
        emit onTrainPass(anim->getEntity()->getId(), px,py);
        anim->pauseSteps(60);
    }
}

/**
 * @brief MapRenderer::onVideoStateChange Wird aufgerufen wenn der Status des Videos sich ändert.
 * @param state Der neue Status.
 */
void MapRenderer::onVideoStateChange(QMediaPlayer::State state)
{
    qDebug() << state;
    if(state == QMediaPlayer::EndOfMedia) {
        dataModel->mainWindow->setCentralWidget(this);
    }else if(state == QMediaPlayer::PlayingState) {
        dataModel->mainWindow->setCentralWidget(videoWidget);
    }
}


