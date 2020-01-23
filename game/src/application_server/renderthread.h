#ifndef RENDERTHREAD_H
#define RENDERTHREAD_H

#include <QThread>
#include "maprenderer.h"

class RenderThread: public QThread
{
public:
    RenderThread(MapRenderer *);
    void run() override;

private:
    MapRenderer * renderer;
};

#endif // RENDERTHREAD_H
