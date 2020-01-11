#ifndef ROUTEINTERFACE_H
#define ROUTEINTERFACE_H

#include <QDockWidget>

#include "trainrenderer.h"

class RouteInterface: public QDockWidget
{
public:
    RouteInterface();

private:
    TrainRenderer * trainRenderer;

public slots:
    void toggle();
};

#endif // ROUTEINTERFACE_H
