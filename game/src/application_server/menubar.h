#ifndef MENUBAR_H
#define MENUBAR_H
#include <QToolBar>
#include <QInputDialog>
#include <QMediaPlayer>
#include "scene.h"
#include "datamodel.h"
#include "view.h"
#include "routeinterface.h"
#include "maprenderer.h"
#include "routeListInterface.h"

class MenuBar: public QToolBar
{
   Q_OBJECT

public:
    MenuBar(Scene* pScene, MapRenderer * pRenderer, DataModel * pDataModel, View * pView, RouteInterface *, RouteListInterface *, QMediaPlayer *);

private:
    Scene* scene;
    DataModel * dataModel;
    MapRenderer * mapRenderer;
    View * view;
    RouteInterface * routeInterface;
    RouteListInterface * routeListInterface;

private slots:

    void slotOpenConnection();
    void slotCloseConnection();

public slots:

};

#endif // MENUBAR_H
