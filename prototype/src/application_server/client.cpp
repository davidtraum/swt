#include "client.h"

/**
 * @brief Client::Client Erzeugt einen neuen Client.
 */
Client::Client(Scene * pScene)
{
    scene = pScene;
    socket = new QTcpSocket(this);
    socket->connectToHost("localhost",50506);
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

void Client::processCommand(QString cmd){
    QStringList split = cmd.split(" ");
    if(split[0].startsWith("TILE") && split.length()==5){
        scene->setTileAt(split[1].toInt(), split[2].toInt(), MapTile::CITY, split[4].toInt());
    }
}
