#include <QApplication>
#include <QMenuBar>
#include <QDebug>
#include <QAction>
#include <QTextItem>

#include "mainwindow.h"
#include "main.h"
#include "view.h"
#include "scene.h"
#include "graphicsmanager.h"

GraphicsManager * graphics;
MainWindow * mainWindow;
/**
 * @brief main Startmethode.
 * @param argc Anzahl der Parameter
 * @param argv Startparameter
 * @return Exit-Code (0=Alles gut)
 */
int main(int argc, char *argv[])
{
    qDebug() << "Spiel wird gestartet.";
    QApplication a(argc, argv);
    mainWindow = new MainWindow();

    mainWindow->setWindowTitle("Railroad Tycoon Prototyp");
    mainWindow->setWindowIcon(QIcon(":/images/schienen/schiene_h.png"));

    graphics = new GraphicsManager();

    Scene * scene;
    View * view;

    scene = new Scene();
    scene->generateWorld();

    view = new View(scene);
    view->setScene(scene);

    mainWindow->setCentralWidget(view);

    mainWindow->menuBar()->addMenu("Spiel")->addMenu("Karte")->addMenu("Neue Karte generieren");


    mainWindow->show();
    return a.exec();
}
