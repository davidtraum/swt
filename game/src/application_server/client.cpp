#include "client.h"
#include "main.h"
#include "routeListInterface.h"
#include <QTimer>
#include <QDebug>
#include <QObject>

/**
 * @brief Client::Client Erzeugt einen neuen Client.
 */
Client::Client(QString * connectionInfo, Scene * pScene, MapRenderer * pMapRenderer, View * pView, DataModel * pDataModel, RouteListInterface * pRouteListInterface)
{
    tickcount=0;
    scene = pScene;
    mapRenderer = pMapRenderer;
    routeListInterface = pRouteListInterface;
    dataModel = pDataModel;
    dataModel->setConnectionInfo(*connectionInfo);
    QStringList split = connectionInfo->split(":");
    QString iP = split[0];
    unsigned short int port =  quint16(split[1].toInt());
    //connect(this, &Client::tileChanged, scene, &Scene::onSetTile);
    connect(this, &Client::tileChanged, mapRenderer, &MapRenderer::onTileChange);
    connect(dataModel, &DataModel::positionChange, this, &Client::onPositionChange);
    connect(this, &Client::playerPositionChange, scene, &Scene::updatePlayerPosition);
    connect(mapRenderer, &MapRenderer::leftclick, this, &Client::onLeftclick);
    connect(this, &Client::onMapLoaded, dataModel, &DataModel::setMapLoaded);
    emit onMapLoaded(false);
    socket = new QTcpSocket(this);
    socket->connectToHost(iP, port);

    debug = true;

    socket->waitForConnected(3000);

    start();

    qDebug() << "[CLIENT] Thread Gestartet.";
}

/**
 * @brief Client::run Startet den Client-Thread.
 */
void Client::run() {
    QStringList split;
    QString data;
    QString buffer = "";
    QString overshoot = "";
    int length = 0;
    while(true){
        //socket->waitForReadyRead();
        if (socket->bytesAvailable()>0){
                /**
                socket->waitForReadyRead();
                data = socket->read(1);
                split = data.split("~");
                length = split.length();
                for(int i = 0; i<length-1; i++){
                    if(length>2 && split[1].length()>0){
                        if(i<length-2){
                            processCommand(split[i]);
                        }else{
                            if(i==length-2){
                                if(split[length-1].length() > 0){
                                    processCommand(split[i]);
                                    overshoot = split[length-1];
                                }else{
                                    overshoot = split[i];
                                }
                            }
                        }
                    }else{
                        overshoot = data;
                    }
                }

                */

            data = socket->read(1);

                if(data.contains("~")) {
                    //qDebug() << "Länge der gelesenen Daten (Socket): " + QString::number(buffer.length());
                    //QStringList strList = data.split("~");
                    processCommand(buffer);
                    buffer = "";
                }
                else {

                    buffer += data;
                    qDebug() << buffer;     //Wenn man das hier rausnimmt stürzt das Programm ab

                }

            //socket->flush();

        }
    }
    //socket->deleteLater();
}

void Client::requestMap(){
    socket->write("MAP GET~");
}

void Client::requestRoutes() {
    socket->write("ROUTE GET~");
    qDebug() << "ROUTE GET~ an Server gesendet";
}

void Client::sendRoute(QString routeString){
    qDebug() << "An Socket: " + routeString;
    socket->write(routeString.toLocal8Bit());
}

/**
 * @brief Client::processCommand Führt einen empfangenen Befehl aus dem Serverprotokoll aus.
 * @param cmd Der Befehl als String.
 */
void Client::processCommand(QString cmd){
    if(debug) {
        qDebug() << "[CLIENT] Command: " + cmd;
    }

    if (cmd.trimmed().isEmpty() || cmd.isEmpty()) {
        return;
    }

    try {

        QStringList split = cmd.split("+");

        if(split.length()>1){
            if((split[1]=="TILE") && split.length()==6){
                emit tileChanged(split[2].toInt(),split[3].toInt(), split[4].toInt(), split[5].toInt());
            }
            else if(split[1]=="POS" && split.length()==4){
                emit playerPositionChange(split[2].toInt(), split[3].toInt());
            }
            else if(split[1]=="MAP"){
                if(split[2]=="DONE"){
                    qDebug() << "Map loaded";
                    sleep(100);
                    emit onMapLoaded(true);
                }
            }
            else if (split[1]=="ROUTES") {
                for (int i= 0; i < split.length(); i++) {

                    //tmpRoutes[i] = split[i+2];
                    //qDebug() << "Empfangen: " + tmpRoutes[i];
                }

            }
            else if(split[1]=="TIME" && split.length()==3){
                dataModel->setTime(split[2].toInt());
            }
            else if(split[1] == "ROUTE" && split.length()==5){
                mapRenderer->animateMovement(QImage(":/images/train_top.png"), split[4]);
            }

        }



    } catch (...) {
        qDebug() << "Client error";
    }

}


/**
 * @brief Client::onPositionChange Slot für Ändern der Position.
 * @param pX Der X-Index.
 * @param pY Der Y-Index.
 */
void Client::onPositionChange(int pX, int pY){
    //qDebug() << QString::fromStdString("POS " + std::to_string(pX) + " " + std::to_string(pY) + "~").toLocal8Bit();
    socket->write(QString::fromStdString("POS " + std::to_string(pX) + " " + std::to_string(pY) + "~").toLocal8Bit());
    //socket->flush();
}

/**
 * @brief Client::onLeftclick Führt einen Linksclick durch.
 */
void Client::onLeftclick(){
    qDebug() << "<olc" << " " << dataModel->getMode();
    switch(dataModel->getMode()){
        case DataModel::TRAIN_STATION:
            socket->write(QString::fromStdString("BUILD STATION " + std::to_string(dataModel->getHoverX()) + " " + std::to_string(dataModel->getHoverY()) + " STATION~").toLocal8Bit());
            socket->flush();
            break;
        case DataModel::TRAIN_DEPOT:
            socket->write(QString::fromStdString("BUILD STATION " + std::to_string(dataModel->getHoverX()) + " " + std::to_string(dataModel->getHoverY()) + " DEPOT~").toLocal8Bit());
            socket->flush();
            break;
        case DataModel::TRAIN_TERMINAL:
            socket->write(QString::fromStdString("BUILD STATION " + std::to_string(dataModel->getHoverX()) + " " + std::to_string(dataModel->getHoverY()) + " TERMINAL~").toLocal8Bit());
            socket->flush();
            break;
        case DataModel::RAIL_PLACEMENT:
            socket->write(QString::fromStdString("BUILD RAIL " + std::to_string(dataModel->getHoverX()) + " " + std::to_string(dataModel->getHoverY()) + "~").toLocal8Bit());
            socket->flush();
            break;
        case DataModel::BRIDGE:
            socket->write(QString::fromStdString("BUILD RAIL " + std::to_string(dataModel->getHoverX()) + " " + std::to_string(dataModel->getHoverY()) + "~").toLocal8Bit());
            socket->flush();
            break;
        case DataModel::REMOVE:
            socket->write(QString::fromStdString("REMOVE " + std::to_string(dataModel->getHoverX()) + " " + std::to_string(dataModel->getHoverY()) + "~").toLocal8Bit());
            socket->flush();
            break;
    }
}

/**
 * @brief Client::onRightclick Führt einen Rechtsklick durch
 */
void Client::onRightclick()
{
    socket->write(QString::fromStdString("BUILD INTERACT " + std::to_string(dataModel->getHoverX()) + " " + std::to_string(dataModel->getHoverY()) + "~").toLocal8Bit());
    socket->flush();
}


