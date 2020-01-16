#ifndef ROUTELISTINTERFACE_H
#define ROUTELISTINTERFACE_H

#include <QDockWidget>
#include <QListWidget>
#include <QPushButton>

#include "graphicsmanager.h"

class RouteListInterface : public QDockWidget
{
    Q_OBJECT
public:
    explicit RouteListInterface();
    QListWidget * routeList;

private:


signals:
    void sendRequestRoutes();

public slots:
    void toggle();
    void deleteRoute();
};

#endif // ROUTELISTINTERFACE_H
