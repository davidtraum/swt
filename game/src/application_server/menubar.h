#ifndef MENUBAR_H
#define MENUBAR_H
#include <QToolBar>
#include <QInputDialog>
#include "scene.h"
#include "datamodel.h"
#include "view.h"

class MenuBar: public QToolBar
{
   // Q_OBJECT

public:
    MenuBar(Scene* pScene, DataModel * pDataModel, View * pView);

private:
    Scene* scene;
    DataModel * dataModel;
    View * view;

private slots:

    void slotOpenConnection();
    void slotCloseConnection();
};

#endif // MENUBAR_H
