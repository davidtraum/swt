#include <QApplication>
#include <QMenuBar>
#include <QDebug>
#include <QAction>
#include <QTextItem>
#include <QTimer>
#include <QDockWidget>
#include <QWidget>
#include <QGridLayout>
#include <QInputDialog>
#include <QToolBar>
#include <QToolButton>

#include "mainwindow.h"
#include "main.h"
#include "view.h"
#include "scene.h"
#include "graphicsmanager.h"
#include "sidepanel.h"
#include "tooltipmenu.h"




GraphicsManager * graphics;
MainWindow * mainWindow;
DataModel * dataModel;
bool gameRunning = true;
View * view;
Scene * scene;
SidePanel * sidePanel;
Client * client;



void timeTicker(){
    dataModel->timeTick();
    QTimer::singleShot(20, []{timeTicker();});
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

    scene = new Scene(graphics);


    ToolTipMenu * tooltip = new ToolTipMenu();


    view = new View(scene, tooltip);
    view->setScene(scene);
    view->setDataModel(dataModel);

    QTimer::singleShot(0, []{
      mainWindow->setCentralWidget(view);
    });

    tooltip->setParent(view);
    tooltip->show();

    QWidget * widget = new QWidget(mainWindow);
    QGridLayout * layout = new QGridLayout(widget);
    widget->setLayout(layout);

    MenuBar * menuBar = new MenuBar(scene, dataModel);
    mainWindow->setMenuBar(menuBar);

    sidePanel = new SidePanel();
    sidePanel->setParent(mainWindow);
    sidePanel->hookDataModel(dataModel);

    QDockWidget dockWidget;
    dockWidget.setFeatures(QDockWidget::DockWidgetMovable);
    dockWidget.setWidget(sidePanel);
    mainWindow->addDockWidget(Qt::DockWidgetArea::RightDockWidgetArea, &dockWidget);



    view->resetMatrix();
    view->currentScale=0.05;
    view->scale(0.05, 0.05);
    //view->enableAnimation();
    //view->fluidZoom(1, true);

    mainWindow->show();

    timeTicker();    

    QToolBar * toolbar = mainWindow->addToolBar("toolbar");
    toolbar->setMovable(false);

    QToolButton * buildButton = new QToolButton(mainWindow);
    buildButton->setToolTip("Bauen");
    buildButton->setIcon(QIcon(QPixmap::fromImage(QImage(":/icons/tools.svg"))));
    buildButton->setPopupMode(QToolButton::InstantPopup);
    buildButton->setCursor(QCursor(Qt::PointingHandCursor));
    QMenu *buildMenu=new QMenu(buildButton);
    buildMenu->addAction(new QAction(QIcon(QPixmap::fromImage(QImage(":/icons/trainstation.svg"))),"Bahnhof bauen", mainWindow));
    buildMenu->addAction(new QAction(QIcon(QPixmap::fromImage(QImage(":/icons/bridge.svg"))),"Brücke bauen", mainWindow));
    buildMenu->addAction(new QAction(QIcon(QPixmap::fromImage(QImage(":/icons/rail.svg"))),"Schienen verlegen", mainWindow));
    buildButton->setMenu(buildMenu);
    toolbar->addWidget(buildButton);

    toolbar->addSeparator();

    QToolButton * trainButton = new QToolButton(mainWindow);
    trainButton->setToolTip("Zugsteuerung");
    trainButton->setIcon(QIcon(QPixmap::fromImage(QImage(":/icons/train.svg"))));
    trainButton->setPopupMode(QToolButton::InstantPopup);
    trainButton->setCursor(QCursor(Qt::PointingHandCursor));
    QMenu *trainMenu=new QMenu(trainButton);
    trainMenu->addAction(new QAction(QIcon(QPixmap::fromImage(QImage(":/icons/create_route.svg"))),"Route erzeugen", mainWindow));
    trainMenu->addAction(new QAction(QIcon(QPixmap::fromImage(QImage(":/icons/show_routes.svg"))),"Routen anzeigen", mainWindow));
    trainButton->setMenu(trainMenu);
    toolbar->addWidget(trainButton);

    QLabel * startscreen = new QLabel();
    startscreen->setPixmap(QPixmap::fromImage(QImage(":/images/highres/startscreen.jpg")));
    mainWindow->setCentralWidget(startscreen);

    a.exec();
}

