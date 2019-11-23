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
#include "gameloop.h"




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

    mainWindow->setWindowTitle("Railroad Tycoon");
    mainWindow->setWindowIcon(QIcon(":/images/highres/icon.png"));

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

    MenuBar * menuBar = new MenuBar(scene, dataModel, view);
    mainWindow->setMenuBar(menuBar);

    sidePanel = new SidePanel();
    sidePanel->setParent(mainWindow);
    sidePanel->hookDataModel(dataModel);

    QDockWidget dockWidget;
    dockWidget.setWidget(sidePanel);
    dockWidget.setFeatures(QDockWidget::NoDockWidgetFeatures);
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

    QToolButton * resetModeButton = new QToolButton(mainWindow);
    resetModeButton->setToolTip("Standardmodus");
    resetModeButton->setIcon(QIcon(QPixmap::fromImage(QImage(":/icons/mouse.svg"))));
    resetModeButton->setCursor(QCursor(Qt::PointingHandCursor));
    resetModeButton->connect(resetModeButton, &QToolButton::clicked, dataModel, &DataModel::setDefaultMode);
    toolbar->addWidget(resetModeButton);


    toolbar->addSeparator();

    QToolButton * buildButton = new QToolButton(mainWindow);
    buildButton->setToolTip("Bauen");
    buildButton->setIcon(QIcon(QPixmap::fromImage(QImage(":/icons/tools.svg"))));
    buildButton->setPopupMode(QToolButton::InstantPopup);
    buildButton->setCursor(QCursor(Qt::PointingHandCursor));
    QMenu *buildMenu=new QMenu(buildButton);
    QAction * trainStationEditor = new QAction(QIcon(QPixmap::fromImage(QImage(":/icons/trainstation.svg"))),"Bahnhof bauen", mainWindow);
    trainStationEditor->connect(trainStationEditor, &QAction::triggered, dataModel, &DataModel::setTrainStationMode);
    buildMenu->addAction(trainStationEditor);
    QAction * bridgeEditor = new QAction(QIcon(QPixmap::fromImage(QImage(":/icons/bridge.svg"))),"Brücke bauen", mainWindow);
    bridgeEditor->connect(bridgeEditor, &QAction::triggered, dataModel, &DataModel::setBridgeMode);
    buildMenu->addAction(bridgeEditor);
    QAction * railEditor = new QAction(QIcon(QPixmap::fromImage(QImage(":/icons/rail.svg"))),"Schienen verlegen", mainWindow);
    railEditor->connect(railEditor, &QAction::triggered, dataModel, &DataModel::setRailPlacementMode);
    buildMenu->addAction(railEditor);
    buildButton->setMenu(buildMenu);
    toolbar->addWidget(buildButton);

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

    QWidget *spacerWidget = new QWidget(mainWindow);
    spacerWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    toolbar->addWidget(spacerWidget);

    QLabel * statusLabel = new QLabel();
    statusLabel->setStyleSheet("margin-right: 75px;");
    toolbar->addWidget(statusLabel);
    dataModel->setStatusDisplayLabel(statusLabel);


    QLabel * startscreen = new QLabel();
    startscreen->setPixmap(QPixmap::fromImage(QImage(":/images/highres/startscreen.jpg")));
    mainWindow->setCentralWidget(startscreen);

    GameLoop * loop = new GameLoop(view,scene,dataModel);
    loop->start();

    a.exec();
}

