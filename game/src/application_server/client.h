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

class Client: public QThread
{
    Q_OBJECT
public:
    Client(QString * connectionInfo, Scene * pScene, View * pView, DataModel * pDataModel);
    void run() override;
    void requestMap();

private:
    QTcpSocket * socket;
    Scene * scene;
    DataModel * dataModel;
    bool debug;
    int tickcount{0};
    void processCommand(QString command);

signals:
    void mapLoaded();
    void tileChanged(int,int,int,int);
    void playerPositionChange(int,int);
    void onMapLoaded(bool);

public slots:
    void onPositionChange(int,int);
    void onLeftclick();
    void onRightclick();
    void sendRoute(QString);

};

#endif // CLIENT_H
