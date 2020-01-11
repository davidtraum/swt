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
#include <QFontDatabase>
#include <QImage>
#include <QGridLayout>

#include "mainwindow.h"
#include "main.h"
#include "view.h"
#include "scene.h"
#include "graphicsmanager.h"
#include "sidepanel.h"
#include "tooltipmenu.h"
#include "gameloop.h"
#include "animationmanager.h"


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
    qDebug() << QFontDatabase::addApplicationFont(":/fonts/mono.ttf");
    mainWindow = new MainWindow();
    //mainWindow->setCursor(QCursor(QPixmap(":/images/highres/cursor.png"), 0,0));
    a.setFont(QFont(QFontDatabase::applicationFontFamilies(0).at(0)));

    mainWindow->setWindowTitle("Railroad Tycoon");
    mainWindow->setWindowIcon(QIcon(":/images/highres/icon.png"));

    graphics = new GraphicsManager();


    dataModel = new DataModel();

    AnimationManager * animationManager = new AnimationManager();
    dataModel->setAnimationManager(animationManager);

    scene = new Scene(graphics, dataModel);



    ToolTipMenu * tooltip = new ToolTipMenu();


    view = new View(scene, tooltip);
    view->setScene(scene);
    view->setDataModel(dataModel);

    QTimer::singleShot(2000, []{
      mainWindow->setCentralWidget(view);
    });

    tooltip->setParent(view);
    tooltip->show();

    QWidget * widget = new QWidget(mainWindow);
    QGridLayout * layout = new QGridLayout(widget);
    widget->setLayout(layout);

    MenuBar * menuBar = new MenuBar(scene, dataModel, view);
    menuBar->setParent(mainWindow);
    menuBar->show();
    menuBar->setStyleSheet("background-color: rgb(150,150,255); color: black;");
    mainWindow->addToolBar(menuBar);


    Minimap * map = new Minimap(300,300, scene, view, dataModel);
    QGridLayout * viewLayout = new QGridLayout();
    map->setAttribute( Qt::WA_TransparentForMouseEvents );
    QWidget *spacerWidget = new QWidget();
    spacerWidget->setAttribute( Qt::WA_TransparentForMouseEvents );
    spacerWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    viewLayout->addWidget(spacerWidget,0,1);
    viewLayout->addWidget(spacerWidget,1,0);
    viewLayout->addWidget(map,0,2);

    view->setLayout(viewLayout);



    view->resetMatrix();
    view->currentScale=0.05;
    view->scale(0.05, 0.05);
    view->enableAnimation();
    view->fluidZoom(1, true);

    mainWindow->show();

    timeTicker();



    QLabel * startscreen = new QLabel();
    startscreen->setPixmap(QPixmap::fromImage(QImage(":/images/highres/startscreen.jpg")));
    mainWindow->setCentralWidget(startscreen);


    GameLoop * loop = new GameLoop(view,scene,dataModel,client,animationManager);
    loop->start();

    a.exec();
}
