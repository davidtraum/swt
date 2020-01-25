#include "client.h"
#include "main.h"
#include "routeListInterface.h"
#include <QTimer>
#include <QDebug>
#include <QObject>
#include <QVideoWidget>

/**
 * @brief Client::Client Erzeugt einen neuen Client.
 */
Client::Client(QString * connectionInfo, Scene * pScene, MapRenderer * pMapRenderer, DataModel * pDataModel, RouteListInterface * pRouteListInterface)
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
    connect(mapRenderer, &MapRenderer::onTrainPass, this, &Client::sendTrainPass);
    emit onMapLoaded(false);
    socket = new QTcpSocket(this);
    socket->connectToHost(iP, port);

    debug = false;

    QWidget::connect(this, &Client::sendRouteString, routeListInterface, &RouteListInterface::receiveRoutes);
    QWidget::connect(routeListInterface, &RouteListInterface::sendDeleteSignal, this, &Client::cancelRoute);

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
    QByteArray input;
    int count = 0;
    while(true){
        //socket->waitForReadyRead();
        if (socket->bytesAvailable()>0){
            input = socket->read(1);
            if(input.at(0) == char(255)){
                while(socket->bytesAvailable()<=0);
                input = socket->read(1);
                while(socket->bytesAvailable()<input[0]);
                data = socket->read(input[0]);
                processCommand(data);
                count++;
                if(count>2){
                    msleep(1);
                    count=0;
                }
            }

            //socket->flush();

        }
    }
    //socket->deleteLater();
}

/**
 * @brief Client::requestMap Fragt beim Server die gesamten Kartendaten an
 */
void Client::requestMap(){
    socket->write("MAP GET~");
}
/**
 * @brief Client::requestRoutes Fragt beim Server eine Liste aller Routen des Spielers an.
 */
void Client::requestRoutes() {
    socket->write("ROUTE GET~");
    qDebug() << "ROUTE GET~ an Server gesendet";
}

/**
 * @brief Client::cancelRoute Schickt einen Befehl zum Server die entsprechende Route zu löschen.
 * @param item Das Item des QListWidget der ausgewählten Zeile.
 */
void Client::cancelRoute(QListWidgetItem * item) {
    qDebug() << "cancel Route called";
    QString handOver = item->text();
    QStringList handOverList = handOver.split(":");
    handOver = "ROUTE DELETE " + handOverList[0] + "~";
    qDebug() << "HandOver: " + handOver;
    socket->write(handOver.toLocal8Bit());

}

/**
 * @brief Client::sendTrainPass Sendet eine Zugposition.
 * @param px Die X-Koordinate.
 * @param py Die Y-Koordinate.
 * @param pid Die ID vom Zug.
 */
void Client::sendTrainPass(int pid, int px, int py)
{
    socket->write(QString("ROUTE PASS " + QString::number(pid) + " " + QString::number(px) + " " + QString::number(py) + "~").toLocal8Bit());
}

/**
 * @brief Client::sendRoute Schicke die Daten einer neuen Route an den Server, sodass dieser diese speichern kann.
 * @param routeString Der String mit den Daten über die Route (Name + Koordinaten + Wagons)
 */
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
        splitPointer = new QStringList(split);

        if(split.length()>1){
            if((split[0]=="TILE") && split.length()==5){
                emit tileChanged(split[1].toInt(),split[2].toInt(), split[3].toInt(), split[4].toInt());
            }
            else if(split[0]=="POS" && split.length()==3){
                emit playerPositionChange(split[1].toInt(), split[2].toInt());
            }
            else if(split[0]=="MAP"){
                if(split[1]=="DONE"){
                    qDebug() << "Map loaded";
                    emit onMapLoaded(true);
                }
            }
            else if (split[0]=="ROUTES") {
                qDebug() << "Angekommen!";
                emit sendRouteString(splitPointer);
            }
            else if(split[0]=="TIME" && split.length()==2){
                dataModel->setTime(split[1].toInt());
            }
            else if(split[0] == "ROUTE" && split.length()==4){  //Starte Animation
                mapRenderer->animateMovementTracked(QImage(":/images/train_top.png"), split[3], split[2].toInt());
            }
            else if(split[0] == "ROUTE" && split.length()==3) {    //Beende Animation
                qDebug() << "Route mit folgender ID wird nicht mehr wiederholt: " << split[2];
                mapRenderer->deleteAnimationId(split[2].toInt());
            }
            else if(split[0] == "SYNC"){
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
        default:
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





