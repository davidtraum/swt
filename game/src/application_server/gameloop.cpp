#include "gameloop.h"

GameLoop::GameLoop(View * pView, Scene * pScene, DataModel * pModel):
    view{pView},scene{pScene},dataModel{pModel}
{

}

/**
 * @brief GameLoop::run Die Gameloop
 */
void GameLoop::run()
{
    while(true){
        QThread::msleep(20);
        view->tick();
        scene->tick();
    }
}
