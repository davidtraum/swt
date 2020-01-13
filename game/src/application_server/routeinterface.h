#ifndef ROUTEINTERFACE_H
#define ROUTEINTERFACE_H

#include <QDockWidget>
#include <QListWidget>

#include "trainrenderer.h"
#include "graphicsmanager.h"
#include "goodselector.h"

class RouteInterface: public QDockWidget
{
    Q_OBJECT
public:
    RouteInterface(GraphicsManager *);

private:
    TrainRenderer * trainRenderer;
    QListWidget * trainstationList;
    GoodSelector * goodSelector;

public slots:
    void toggle();
    void trainStationSelected(int,int);
    void addWagon(QString *);
};

#endif // ROUTEINTERFACE_H
