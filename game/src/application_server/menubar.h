#ifndef MENUBAR_H
#define MENUBAR_H
#include <QMenuBar>
#include <QInputDialog>
#include "scene.h"
#include "datamodel.h"

class MenuBar: public QMenuBar
{
   // Q_OBJECT

public:
    MenuBar(Scene* pScene, DataModel * pDataModel);

private:
    Scene* scene;
    DataModel * dataModel;

private slots:

    void slotOpenConnection();
    void slotCloseConnection();
};

#endif // MENUBAR_H
