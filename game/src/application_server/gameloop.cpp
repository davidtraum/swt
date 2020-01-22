#include "gameloop.h"
#include <iostream>

#include <ctime>

#include <QDebug>

using namespace std;

GameLoop::GameLoop(MapRenderer * pView, Scene * pScene, DataModel * pModel, Client * pClient):
    view{pView},scene{pScene},dataModel{pModel},client{pClient}
{

}

/**
 * @brief GameLoop::run Die Gameloop
 */
void GameLoop::run()
{
    while(true){
        QThread::msleep(1);
        view->tick();
    }
}
