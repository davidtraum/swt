#ifndef GAMELOOP_H
#define GAMELOOP_H

#include <QThread>

#include "view.h"
#include "scene.h"
#include "datamodel.h"
#include "client.h"

class GameLoop: public QThread
{
public:
    GameLoop(View *, Scene *, DataModel *, Client *);
    void run() override;

private:
    View * view;
    Scene * scene;
    DataModel * dataModel;
    Client * client;
};

#endif // GAMELOOP_H
