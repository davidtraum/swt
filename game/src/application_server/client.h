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
    void processCommand(QString command);

signals:
    void mapLoaded();
    void tileChanged(int,int,int,int);
    void playerConnect(int);
    void playerPositionChange(int, int,int);
    void onPlacementAllowedChange(bool);

public slots:
    void onPositionChange(int,int);
    void onLeftclick();
};

#endif // CLIENT_H
