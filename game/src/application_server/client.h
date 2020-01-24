#ifndef CLIENT_H
#define CLIENT_H

#include <QTcpSocket>
#include <QObject>
#include <QThread>
#include <QStringList>
#include <QString>
#include "scene.h"
#include "maptile.h"
#include "datamodel.h"
#include "view.h"
#include "maprenderer.h"
#include "routeListInterface.h"

class Client: public QThread
{
    Q_OBJECT
public:
    Client(QString * connectionInfo, Scene * pScene, MapRenderer * pRenderer, View * pView, DataModel * pDataModel, RouteListInterface *);
    void run() override;
    void requestMap();
    QString * tmpRoutes;

private:
    QTcpSocket * socket;
    Scene * scene;
    DataModel * dataModel;
    MapRenderer * mapRenderer;
    bool debug;
    RouteListInterface * routeListInterface;
    int tickcount{0};
    void processCommand(QString command);
    QStringList * splitPointer;

signals:
    void mapLoaded();
    void tileChanged(int,int,int,int);
    void playerPositionChange(int,int);
    void onMapLoaded(bool);
    QStringList sendRouteString(QStringList *);

public slots:
    void onPositionChange(int,int);
    void onLeftclick();
    void onRightclick();
    void sendRoute(QString);
    void requestRoutes();

};

#endif // CLIENT_H
