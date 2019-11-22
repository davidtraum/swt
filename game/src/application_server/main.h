#ifndef MAIN_H
#define MAIN_H

#include "mainwindow.h"
#include "datamodel.h"
#include <QLabel>
#include <client.h>
#include "menubar.h"

extern MainWindow * mainWindow;
extern bool gameRunning;
extern DataModel * dataModel;
extern Client * client;

#endif // MAIN_H
