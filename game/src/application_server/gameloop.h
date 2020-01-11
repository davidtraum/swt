#ifndef GAMELOOP_H
#define GAMELOOP_H

#include <QThread>

#include "view.h"
#include "scene.h"
#include "datamodel.h"
#include "client.h"
#include "animationmanager.h"

class GameLoop: public QThread
{
public:
    GameLoop(View *, Scene *, DataModel *, Client *, AnimationManager *);
    void run() override;

private:
    View * view;
    Scene * scene;
    DataModel * dataModel;
    Client * client;
    AnimationManager * animationManager;
};

#endif // GAMELOOP_H
