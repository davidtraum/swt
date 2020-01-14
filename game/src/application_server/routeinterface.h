#ifndef ROUTEINTERFACE_H
#define ROUTEINTERFACE_H

#include <QDockWidget>
#include <QListWidget>
#include <QPushButton>

#include "trainrenderer.h"
#include "graphicsmanager.h"
#include "goodselector.h"
#include "client.h"

class RouteInterface: public QDockWidget
{
    Q_OBJECT
public:
    RouteInterface(GraphicsManager *);
    int wagonCount;
    TrainRenderer * trainRenderer;


private:
    QListWidget * trainstationList;
    GoodSelector * goodSelector;
    QPushButton * confirmBtn;

public slots:
    void toggle();
    void trainStationSelected(int,int);
    void addWagon(QString *);
    void confirmRoute();
    void removeWagon();
signals:
    void sendConfirmRoute(QString);
};

#endif // ROUTEINTERFACE_H
