#include <QApplication>
#include <QMenuBar>
#include <QDebug>
#include <QAction>
#include <QTextItem>
#include <QTimer>
#include <QDockWidget>
#include <QWidget>
#include <QGridLayout>

#include "mainwindow.h"
#include "main.h"
#include "view.h"
#include "scene.h"
#include "graphicsmanager.h"
#include "sidepanel.h"



GraphicsManager * graphics;
MainWindow * mainWindow;
DataModel * dataModel;
bool gameRunning = true;
View * view;
Scene * scene;
SidePanel * sidePanel;

double scale = 0.01;

void introAnimation(){
    scale+=0.01;
    view->resetMatrix();
    view->scale(scale,scale);

    if(scale<1){
        QTimer::singleShot(10, []{introAnimation();});
    }
}


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

    dataModel = new DataModel();

    scene = new Scene();
    scene->generateWorld();

    view = new View(scene);
    view->setScene(scene);

    mainWindow->setCentralWidget(view);

    QWidget * widget = new QWidget(mainWindow);
    QGridLayout * layout = new QGridLayout(widget);
    widget->setLayout(layout);

    sidePanel = new SidePanel();
    sidePanel->setParent(mainWindow);
    sidePanel->hookDataModel(dataModel);

    QDockWidget dockWidget;
    dockWidget.setFeatures(QDockWidget::DockWidgetMovable);
    dockWidget.setWidget(sidePanel);
    mainWindow->addDockWidget(Qt::DockWidgetArea::RightDockWidgetArea, &dockWidget);



    introAnimation();

    mainWindow->show();

    return a.exec();
}
