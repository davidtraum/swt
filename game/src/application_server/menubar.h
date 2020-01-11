#ifndef MENUBAR_H
#define MENUBAR_H
#include <QToolBar>
#include <QInputDialog>
#include "scene.h"
#include "datamodel.h"
#include "view.h"
#include "routeinterface.h"

class MenuBar: public QToolBar
{
   Q_OBJECT

public:
    MenuBar(Scene* pScene, DataModel * pDataModel, View * pView, RouteInterface *);

private:
    Scene* scene;
    DataModel * dataModel;
    View * view;
    RouteInterface * routeInterface;

private slots:

    void slotOpenConnection();
    void slotCloseConnection();
};

#endif // MENUBAR_H
