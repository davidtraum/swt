#ifndef CLIENT_H
#define CLIENT_H

#include <QTcpSocket>
#include <QObject>
#include <QThread>
#include <QStringList>
#include <QString>
#include "scene.h"
#include "maptile.h"

class Client: public QThread
{
public:
    Client(Scene * pScene);
    void run() override;

private:
    QTcpSocket * socket;
    Scene * scene;
    void processCommand(QString command);
};

#endif // CLIENT_H
