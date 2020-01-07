#include "gameloop.h"
#include <iostream>
#include <conio.h>

using namespace std;

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
