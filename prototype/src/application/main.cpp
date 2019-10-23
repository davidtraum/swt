#include "mainwindow.h"

#include <QApplication>
#include <QMenuBar>
#include <QDebug>
#include <QAction>

#include "main.h"
#include "view.h"
#include "scene.h"
#include "graphicsmanager.h"

GraphicsManager * graphics;
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
    MainWindow w;

    w.setWindowTitle("Railroad Tycoon Prototyp");
    w.setFixedSize(1000,600);

    QMenu * menu = w.menuBar()->addMenu("Spiel");
    QMenu * map = menu->addMenu("Karte");
    w.menuBar()->addMenu("Einstellungen");

    graphics = new GraphicsManager();

    Scene * scene;
    View * view;

    scene = new Scene();
    scene->generateWorld();

    view = new View();
    view->setScene(scene);

    w.setCentralWidget(view);


    w.show();
    return a.exec();
}
