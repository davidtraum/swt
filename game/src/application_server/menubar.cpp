#include "menubar.h"
#include "infowidget.h"
#include "client.h"
#include "datamodel.h"

#include <QDebug>
#include <QIcon>
#include <QTimer>
#include <QImage>
#include <QToolButton>
#include <QMenu>
#include <QSlider>


/**
 * @brief MenuBar::MenuBar Erzeugt Menüstruktur.
 */
MenuBar::MenuBar(Scene * pScene, MapRenderer * pRenderer, DataModel * pDataModel, View * pView, RouteInterface * pRouteInterface, RouteListInterface * pRouteListInterface, QMediaPlayer * musicPlayer, InfoWidget * pInfoWidget) :
    scene{pScene}, dataModel{pDataModel}, mapRenderer{pRenderer}, view{pView}, routeInterface{pRouteInterface}, routeListInterface{pRouteListInterface}, infoWidget{pInfoWidget}
{
    this->setStyleSheet("background-color: rgb(150,150,255);");
    this->setMovable(false);

    QToolButton * resetModeButton = new QToolButton(this);
    resetModeButton->setToolTip("Standardmodus");
    resetModeButton->setIcon(QIcon(QPixmap::fromImage(QImage(":/icons/mouse.svg"))));
    resetModeButton->setCursor(QCursor(Qt::PointingHandCursor));
    resetModeButton->connect(resetModeButton, &QToolButton::clicked, dataModel, &DataModel::setDefaultMode);
    resetModeButton->setShortcut(Qt::Key_Q);
    this->addWidget(resetModeButton);


    this->addSeparator();

    QToolButton * buildButton = new QToolButton(this);
    buildButton->setToolTip("Bauen");
    buildButton->setIcon(QIcon(QPixmap::fromImage(QImage(":/icons/tools.svg"))));
    buildButton->setPopupMode(QToolButton::InstantPopup);
    buildButton->setCursor(QCursor(Qt::PointingHandCursor));
    QMenu *buildMenu=new QMenu(buildButton);
    QMenu * trainStationMenu = new QMenu("Bahnhof bauen");
    QAction * depotMode = new QAction(QIcon(QPixmap::fromImage(QImage(":/icons/trainstation.svg"))),"Depot (1.000$)", this);
    depotMode->connect(depotMode, &QAction::triggered, dataModel, &DataModel::setDepotMode);
    trainStationMenu->addAction(depotMode);
    QAction * stationMode = new QAction(QIcon(QPixmap::fromImage(QImage(":/icons/trainstation.svg"))),"Bahnhof (10.000$)", this);
    stationMode->connect(stationMode, &QAction::triggered, dataModel, &DataModel::setTrainStationMode);
    trainStationMenu->addAction(stationMode);
    QAction * terminalMode = new QAction(QIcon(QPixmap::fromImage(QImage(":/icons/trainstation.svg"))),"Terminal(50.000$)", this);
    terminalMode->connect(terminalMode, &QAction::triggered, dataModel, &DataModel::setTerminalMode);
    trainStationMenu->addAction(terminalMode);
    buildMenu->addMenu(trainStationMenu);
    //QAction * bridgeEditor = new QAction(QIcon(QPixmap::fromImage(QImage(":/icons/bridge.svg"))),"Brücke bauen", this);
    //bridgeEditor->connect(bridgeEditor, &QAction::triggered, dataModel, &DataModel::setBridgeMode);
    //bridgeEditor->setShortcut(Qt::Key_2);
    //buildMenu->addAction(bridgeEditor);
    QAction * railEditor = new QAction(QIcon(QPixmap::fromImage(QImage(":/icons/rail.svg"))),"Schienen verlegen", this);
    railEditor->setShortcut(Qt::Key_3);
    railEditor->connect(railEditor, &QAction::triggered, dataModel, &DataModel::setRailPlacementMode);
    buildMenu->addAction(railEditor);
    //QAction * removeEditor = new QAction(QIcon(QPixmap::fromImage(QImage(":/icons/wrecking-ball.svg"))),"Entferne", this);
    //removeEditor->setShortcut(Qt::Key_4);
    //removeEditor->connect(removeEditor, &QAction::triggered, dataModel, &DataModel::setRemoveMode);
    //buildMenu->addAction(removeEditor);

    buildButton->setMenu(buildMenu);
    this->addWidget(buildButton);


    QToolButton * trainButton = new QToolButton(this);
    trainButton->setToolTip("Zugsteuerung");
    trainButton->setIcon(QIcon(QPixmap::fromImage(QImage(":/icons/train.svg"))));
    trainButton->setPopupMode(QToolButton::InstantPopup);
    trainButton->setCursor(QCursor(Qt::PointingHandCursor));
    QMenu *trainMenu=new QMenu(trainButton);

    QAction * createRoute = new QAction(QIcon(QPixmap::fromImage(QImage(":/icons/create_route.svg"))),"Route erzeugen", this);
    connect(createRoute, &QAction::triggered, routeInterface, &RouteInterface::toggle);
    trainMenu->addAction(createRoute);

    QAction * showRouteList = new QAction(QIcon(QPixmap::fromImage(QImage(":/icons/show_routes.svg"))),"Routen anzeigen", this);
    connect(showRouteList, &QAction::triggered, routeListInterface, &RouteListInterface::toggle);
    trainMenu->addAction(showRouteList);

    trainButton->setMenu(trainMenu);
    this->addWidget(trainButton);

    QToolButton * serverButton = new QToolButton(this);
    serverButton->setToolTip("Server");
    serverButton->setIcon(QIcon(QPixmap::fromImage(QImage(":/icons/server.svg"))));
    serverButton->setPopupMode(QToolButton::InstantPopup);
    serverButton->setCursor(QCursor(Qt::PointingHandCursor));
    QMenu *serverMenu=new QMenu(serverButton);
    QAction *openConnection = new QAction(QIcon(QPixmap::fromImage(QImage(":/icons/verbindungsaufbau.svg"))),"Verbindung aufbauen", this);
    connect(openConnection, &QAction::triggered, this, &MenuBar::slotOpenConnection);
    serverMenu->addAction(openConnection);
    serverButton->setMenu(serverMenu);
    this->addWidget(serverButton);

    QSlider * volumeSlider = new QSlider();
    volumeSlider->setFixedWidth(100);
    volumeSlider->setOrientation(Qt::Horizontal);
    volumeSlider->setRange(0,100);
    volumeSlider->setValue(50);
    connect(volumeSlider, &QSlider::valueChanged, musicPlayer, &QMediaPlayer::setVolume);
    this->addWidget(volumeSlider);


    QSlider * speedSlider = new QSlider();
    speedSlider->setFixedWidth(200);
    speedSlider->setOrientation(Qt::Horizontal);
    speedSlider->setRange(0,50);
    speedSlider->setValue(20);
    connect(speedSlider, &QSlider::valueChanged, pRenderer, &MapRenderer::setLogicSpeed);
    this->addWidget(speedSlider);


    QWidget *spacer = new QWidget(this);
    spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    this->addWidget(spacer);

    QLabel * statusLabel = new QLabel();
    statusLabel->setStyleSheet("margin-right: 75px;");
    this->addWidget(statusLabel);
    dataModel->setStatusDisplayLabel(statusLabel);

}

/**
 * @brief MenuBar::openConnection Öffnet Input-Dialog für IP-Adresse und iniitiert Client.
 */
void MenuBar::slotOpenConnection(){

    bool ok;
    QString text = QInputDialog::getText(nullptr,
                                         "Serververbindung",
                                         "IP-Adresse",
                                         QLineEdit::Normal,
                                         "localhost:2000",
                                         &ok);

    if(ok){
        Client * client = new Client(&text, scene, mapRenderer, dataModel, routeListInterface, infoWidget);

        QWidget::connect(routeInterface, &RouteInterface::sendConfirmRoute, client, &Client::sendRoute);

        QWidget::connect(routeListInterface, &RouteListInterface::sendRequestRoutes, client, &Client::requestRoutes);

        QWidget::connect(infoWidget, &InfoWidget::sendInfoSignal, client, &Client::requestInfo);

        QTimer::singleShot(1000, [client]{client->requestMap();});
    }
}

/**
 * @brief MenuBar::closeConnection Schließt die aktuelle Verbindung mit dem Server.
 */
void MenuBar::slotCloseConnection()
{
    qDebug()<<"close";
}

