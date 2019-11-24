#include "client.h"
#include <QTimer>
#include <QDebug>
#include <QObject>

/**
 * @brief Client::Client Erzeugt einen neuen Client.
 */
Client::Client(QString * connectionInfo, Scene * pScene, View * pView, DataModel * pDataModel)
{
    scene = pScene;
    dataModel = pDataModel;
    dataModel->setConnectionInfo(*connectionInfo);
    QStringList split = connectionInfo->split(":");
    QString iP = split[0];
    unsigned short int port =  quint16(split[1].toInt());
    connect(this, &Client::tileChanged, scene, &Scene::onSetTile);
    connect(dataModel, &DataModel::positionChange, this, &Client::onPositionChange);
    connect(this, &Client::playerPositionChange, scene, &Scene::updatePlayerPosition);
    connect(this, &Client::playerConnect, scene, &Scene::addPlayer);
    connect(pView, &View::onLeftclick, this, &Client::onLeftclick);
    socket = new QTcpSocket(this);
    socket->connectToHost(iP, port);

    debug = true;

    start();

    qDebug() << "[CLIENT] Thread Gestartet.";
}

/**
 * @brief Client::run Startet den Client-Thread.
 */
void Client::run() {
    QString data;
    QStringList split;
    QString buffer = "";
    while(true){
        if(socket->bytesAvailable()>1){
            data = socket->read(1).data();
            if(data[0]=='~'){
                processCommand(buffer);
                buffer = "";
            }else{
                buffer+=data;
            }
        }
    }
}

void Client::requestMap(){
    socket->write("MAP GET");
}

/**
 * @brief Client::processCommand Führt einen empfangenen Befehl aus dem Serverprotokoll aus.
 * @param cmd Der Befehl als String.
 */
void Client::processCommand(QString cmd){
    if(debug) qDebug() << "[CLIENT] Command: " + cmd;
    try {
        QStringList split = cmd.split(" ");
        if(split[0].startsWith("TILE") && split.length()==5){
            emit tileChanged(split[1].toInt(),split[2].toInt(), split[3].toInt(), split[4].toInt());
        }else if(split[0].startsWith("P") && split.length()>=3){
            if(split[1].startsWith("C")){
                qDebug() << "Player conn " << split[2];
                emit playerConnect(split[2].toInt());
            }else if(split[1].startsWith("P") && split.length()==5){
                emit playerPositionChange(split[2].toInt(), split[3].toInt(), split[4].toInt());
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
    socket->write(QString::fromStdString("POS " + std::to_string(pX) + " " + std::to_string(pY)).toLocal8Bit());
    socket->flush();
}

/**
 * @brief Client::onTileChange Slot für Ändern eines Tiles.
 * @param pX Der X-Index.
 * @param pY Der Y-Index.
 * @param pType Der Typ.
 * @param pRotation Die Rotation.
 */
void Client::onLeftclick(){
    switch(dataModel->getMode()){
        case DataModel::RAIL_PLACEMENT:
            if(debug){
                qDebug() << "[BUILD] Anfrage für Rail " << dataModel->getHoverX() << " " << dataModel->getHoverY();
            }
            socket->write(QString::fromStdString("BUILD RAIL " + std::to_string(dataModel->getHoverX()) + " " + std::to_string(dataModel->getHoverY())).toLocal8Bit());
            break;
    }
    socket->flush();
}
