#ifndef GAMELOOP_H
#define GAMELOOP_H

#include <QThread>

#include "view.h"
#include "scene.h"
#include "datamodel.h"


class GameLoop: public QThread
{
public:
    GameLoop(View *, Scene *, DataModel *);
    void run() override;

private:
    View * view;
    Scene * scene;
    DataModel * dataModel;
};

#endif // GAMELOOP_H
