#include "renderthread.h"
#include <QDebug>

/**
 * @brief RenderThread::RenderThread Erzeugt einen neuen Render-Thread für einen Map-Renderer.
 * @param pRenderer Ein Map-Renderer.
 */
RenderThread::RenderThread(MapRenderer * pRenderer):
    renderer{pRenderer}
{

}

/**
 * @brief RenderThread::run Führt die Renderschleife aus.
 */
void RenderThread::run()
{
    qDebug() << "Render Thread gestartet";
    while(true){
        QThread::msleep(1);
        renderer->renderFrame();
    }
}
