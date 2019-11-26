#include "gameloop.h"

GameLoop::GameLoop(View * pView, Scene * pScene, DataModel * pModel, Client * pClient):
    view{pView},scene{pScene},dataModel{pModel},client{pClient}
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
