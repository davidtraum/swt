#ifndef ROUTEINTERFACE_H
#define ROUTEINTERFACE_H

#include <QDockWidget>
#include <QListWidget>

#include "trainrenderer.h"
#include "graphicsmanager.h"

class RouteInterface: public QDockWidget
{
public:
    RouteInterface(GraphicsManager *);

private:
    TrainRenderer * trainRenderer;
    QListWidget * trainstationList;

public slots:
    void toggle();
    void trainStationSelected(int,int);
};

#endif // ROUTEINTERFACE_H
