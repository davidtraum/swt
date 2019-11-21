#include "mytcpserver.h"

MyTcpServer::MyTcpServer(QObject *parent): QObject(parent)
{
    server = new QTcpServer(this);

    connect(server, SIGNAL(newConnection()), this, SLOT(newConnection()));

    if(!server->listen(QHostAddress::LocalHost, 9999)){
        qDebug()<<"Server kann nicht starten!"<<endl;
    }
    else{
        qDebug()<<"Server wurde gestartet!"<<endl;
    }
}

void MyTcpServer::newConnection(){

    QTcpSocket *socket = server->nextPendingConnection();

    socket->write("Hallo Client!\n");
    socket->flush();

    socket->waitForBytesWritten(3000);

    socket->close();
    }
