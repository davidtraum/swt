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
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QDir>
#include <QVideoWidget>

#include "mainwindow.h"
#include "main.h"
#include "view.h"
#include "scene.h"
#include "graphicsmanager.h"
#include "sidepanel.h"
#include "tooltipmenu.h"
#include "gameloop.h"
#include "routeinterface.h"
#include "routelistinterface.h"
#include "maprenderer.h"
#include "renderthread.h"
#include "videowidget.h"
#include "infowidget.h"


GraphicsManager * graphics;
MainWindow * mainWindow;
DataModel * dataModel;
bool gameRunning = true;
View * view;
Scene * scene;
SidePanel * sidePanel;
Client * client;
MapRenderer * mapRenderer;
MenuBar * menuBar;



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


    dataModel = new DataModel(mainWindow);

    scene = new Scene(graphics, dataModel);


    ToolTipMenu * tooltip = new ToolTipMenu();


    view = new View(scene, tooltip);
    view->setScene(scene);
    view->setDataModel(dataModel);

    mapRenderer = new MapRenderer(graphics, dataModel);
    QTimer::singleShot(2000, []{
      mainWindow->setCentralWidget(mapRenderer);
      RenderThread * renderThread = new RenderThread(mapRenderer);
      renderThread->start();
      mapRenderer->cloudAnimation();
    });

    RouteInterface * routeInterface = new RouteInterface(graphics);
    mainWindow->addDockWidget(Qt::BottomDockWidgetArea, routeInterface);
    QWidget::connect(mapRenderer, &MapRenderer::tileClick, routeInterface, &RouteInterface::onTileInteract);
    QWidget::connect(routeInterface->trainRenderer, &TrainRenderer::triggerRemoveWagon, routeInterface, &RouteInterface::removeWagon);

    RouteListInterface * routeListInterface = new RouteListInterface();
    mainWindow->addDockWidget(Qt::BottomDockWidgetArea, routeListInterface);


    tooltip->setParent(view);
    tooltip->show();



    //Musik-Playlist: Song hinzufügen mit addMedia()
    QMediaPlayer * player = new QMediaPlayer;
    QMediaPlaylist * playlist = new QMediaPlaylist(player);
    playlist->setPlaybackMode(QMediaPlaylist::Loop);

    for (int i=2; i<4; i++) {
        playlist->addMedia(QUrl("qrc:/data/soundtrack_"+QString::number(i)+".mp3"));
        qDebug() << "Song " << i << " hinzugefügt.";
    }

    playlist->shuffle();


    playlist->setCurrentIndex(0);
    player->setPlaylist(playlist);
    player->play();
    qDebug() << playlist->mediaCount();
    qDebug() << player->isAudioAvailable();
    qDebug() << player->mediaStatus();

    qDebug() << "DANACH";

    Minimap * map = new Minimap(300,300, mapRenderer, dataModel);
    QVBoxLayout * rightLayout = new QVBoxLayout();
    QGridLayout * viewLayout = new QGridLayout();
    QWidget *spacerWidget = new QWidget();
    spacerWidget->setAttribute( Qt::WA_TransparentForMouseEvents );
    spacerWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    viewLayout->addWidget(spacerWidget,0,1);
    viewLayout->addWidget(spacerWidget,1,0);
    viewLayout->addLayout(rightLayout, 0,2);
    rightLayout->addWidget(map);

    QWidget * spacerVert = new QWidget();
    spacerVert->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    spacerVert->setFixedHeight(40);
    spacerVert->setFixedWidth(0);
    rightLayout->addWidget(spacerVert);

    InfoWidget * infoWidget = new InfoWidget();
    rightLayout->addWidget(infoWidget);
    dataModel->setInfoWidget(infoWidget);

    menuBar = new MenuBar(scene,mapRenderer, dataModel, view, routeInterface, routeListInterface, player, infoWidget);
    menuBar->setParent(mainWindow);
    menuBar->show();
    menuBar->setStyleSheet("background-color: rgb(150,150,255); color: black;");
    mainWindow->addToolBar(menuBar);

    mapRenderer->setLayout(viewLayout);

    //QWidget::connect(mapRenderer, &MapRenderer::sendPlayBridge, videoWidget, &Videowidget::toggle);     //Connect spielt Video ab, wenn Brücke gebaut wird

    view->resetMatrix();
    view->currentScale=0.05;
    view->scale(0.05, 0.05);
    view->enableAnimation();
    view->fluidZoom(1, true);

    mainWindow->show();

    timeTicker();

    QLabel * startscreen = new QLabel();
    startscreen->setPixmap(QPixmap::fromImage(QImage(":/images/highres/rrt_logo_grp5.png").scaled(1000,1500,Qt::KeepAspectRatio)));
    startscreen->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    mainWindow->setCentralWidget(startscreen);

    GameLoop * loop = new GameLoop(mapRenderer,scene,dataModel,client);
    loop->start();

    a.exec();

    return 0;
}
