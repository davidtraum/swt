#ifndef MAIN_H
#define MAIN_H

#include "mainwindow.h"
#include "datamodel.h"
#include <QLabel>
#include <client.h>
#include "menubar.h"
#include "sidepanel.h"

extern MainWindow * mainWindow;
extern bool gameRunning;
extern DataModel * dataModel;
extern Client * client;
extern View * view;
extern Scene * scene;
extern SidePanel * sidePanel;
extern MapRenderer * mapRenderer;
extern GraphicsManager * graphics;
extern MenuBar * menuBar;

#endif // MAIN_H
