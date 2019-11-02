#include "client.h"
#include <QTimer>
#include <QDebug>
#include <QObject>

/**
 * @brief Client::Client Erzeugt einen neuen Client.
 */
Client::Client(DataModel * pDataModel, Scene * pScene)
{
    scene = pScene;
    dataModel = pDataModel;
    connect(this, &Client::tileChanged, scene, &Scene::setTileAt);
    connect(dataModel, &DataModel::positionChange, this, &Client::onPositionChange);
    connect(this, &Client::playerPositionChange, scene, &Scene::updatePlayerPosition);
    connect(this, &Client::playerConnect, scene, &Scene::addPlayer);
    socket = new QTcpSocket(this);
    socket->connectToHost(*dataModel->getIP(),dataModel->getPort());
    socket->write("MAP GET");

    start();
}

/**
 * @brief Client::run Startet den Client-Thread.
 */
void Client::run() {
    QString data;
    QStringList split;
    while(true){
        if(socket->bytesAvailable()>3){
            data = socket->read(128).data();
            split = data.split("+");
            for(QString s:split){
                if(s.length()>0)
                processCommand(s);
            }
        }
    }
}

/**
 * @brief Client::processCommand Führt einen empfangenen Befehl aus dem Serverprotokoll aus.
 * @param cmd Der Befehl als String.
 */
void Client::processCommand(QString cmd){
    qDebug() << cmd;
    QStringList split = cmd.split(" ");
    if(split[0].startsWith("TILE") && split.length()==5){
        emit tileChanged(split[1].toInt(),split[2].toInt(), split[3].toInt(), split[4].toInt());
    }else if(split[0].startsWith("PLAYER")){
        if(split[1].startsWith("CONN")){
            emit playerConnect(split[2].toInt());
        }else if(split[1].startsWith("POS")){
            emit playerPositionChange(split[2].toInt(), split[3].toInt(), split[4].toInt());
        }
    }
}


void Client::onPositionChange(int pX, int pY){
    socket->write(QString::fromStdString("POS " + std::to_string(pX) + " " + std::to_string(pY)).toLocal8Bit());
    socket->flush();
}
