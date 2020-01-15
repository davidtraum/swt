#ifndef GAMELOOP_H
#define GAMELOOP_H

#include <QThread>

#include "maprenderer.h"
#include "scene.h"
#include "datamodel.h"
#include "client.h"

class GameLoop: public QThread
{
    Q_OBJECT
public:
    GameLoop(MapRenderer *, Scene *, DataModel *, Client *);
    void run() override;

private:
    MapRenderer * view;
    Scene * scene;
    DataModel * dataModel;
    Client * client;
    long lastRender = 0;
    int frameDelay = 500;
};

#endif // GAMELOOP_H
