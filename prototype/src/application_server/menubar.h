#ifndef MENUBAR_H
#define MENUBAR_H
#include <QMenuBar>
#include <QInputDialog>
#include "scene.h"

class MenuBar: public QMenuBar
{
   // Q_OBJECT

public:
    MenuBar(Scene* pScene);

private:
    Scene* scene;

private slots:

    void slotOpenConnection();
    void slotCloseConnection();
};

#endif // MENUBAR_H
