#include "client.h"
#include <QTimer>
#include <QDebug>
#include <QObject>

/**
 * @brief Client::Client Erzeugt einen neuen Client.
 */
Client::Client(QString * connectionInfo, Scene * pScene, View * pView, DataModel * pDataModel)
{
    tickcount=0;
    scene = pScene;
    dataModel = pDataModel;
    dataModel->setConnectionInfo(*connectionInfo);
    QStringList split = connectionInfo->split(":");
    QString iP = split[0];
    unsigned short int port =  quint16(split[1].toInt());
    connect(this, &Client::tileChanged, scene, &Scene::onSetTile);
    connect(dataModel, &DataModel::positionChange, this, &Client::onPositionChange);
    connect(this, &Client::playerPositionChange, scene, &Scene::updatePlayerPosition);
    connect(pView, &View::onLeftclick, this, &Client::onLeftclick);
    connect(pView, &View::onRightclick, this, &Client::onRightclick);
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
        while(socket->bytesAvailable()>0){
                /*
                data = socket->readAll();
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
                if(data == "~"){
                    processCommand(buffer);
                    buffer = "";
                }else{
                    buffer += data;

                }
        }
    }
    socket->deleteLater();
}

void Client::requestMap(){
    socket->write("MAP GET~");
}

/**
 * @brief Client::processCommand Führt einen empfangenen Befehl aus dem Serverprotokoll aus.
 * @param cmd Der Befehl als String.
 */
void Client::processCommand(QString cmd){
    if(debug) qDebug() << "[CLIENT] Command: " + cmd;
    try {
        QStringList split = cmd.split("+");
        if(split.length()>1){
        if((split[1]=="TILE") && split.length()==6){
            emit tileChanged(split[2].toInt(),split[3].toInt(), split[4].toInt(), split[5].toInt());
        }else if(split[1]=="POS" && split.length()==4){
            emit playerPositionChange(split[2].toInt(), split[3].toInt());
        }else if(split[1]=="MAP"){
            if(split[2]=="DONE"){
                qDebug() << "Map loaded";
                emit onMapLoaded(true);
            }
        }else if(split[1]=="TIME" && split.length()==3){
            dataModel->setTime(split[2].toInt());
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
    qDebug() << "<olc";
    switch(dataModel->getMode()){
        case DataModel::RAIL_PLACEMENT:
            qDebug() << "[BUILD] Anfrage für Rail " << dataModel->getHoverX() << " " << dataModel->getHoverY();
            socket->write(QString::fromStdString("BUILD RAIL " + std::to_string(dataModel->getHoverX()) + " " + std::to_string(dataModel->getHoverY()) + "~").toLocal8Bit());
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


