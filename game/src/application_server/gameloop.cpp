#include "gameloop.h"
#include <iostream>

using namespace std;

GameLoop::GameLoop(View * pView, Scene * pScene, DataModel * pModel, Client * pClient, AnimationManager * pAnimManager):
    view{pView},scene{pScene},dataModel{pModel},client{pClient},animationManager{pAnimManager}
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
        animationManager->tick();
    }
}
