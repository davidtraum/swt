#include "routeinterface.h"

#include <QCursor>
#include <QDebug>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QGroupBox>
#include <QString>
#include "maptile.h"


/**
 * @brief RouteInterface::RouteInterface Erzeugt das Routeninterface.
 */
RouteInterface::RouteInterface(GraphicsManager * gm)
{
    QDockWidget::setFeatures(nullptr);
    QDockWidget::setVisible(false);

    QGroupBox * mainWidget = new QGroupBox(" Route erzeugen");

    QHBoxLayout * layout = new QHBoxLayout(mainWidget);

    trainRenderer = new TrainRenderer(gm);
    layout->addWidget(trainRenderer);

    trainstationList = new QListWidget();
    trainstationList->setFixedWidth(250);
    trainstationList->setMaximumHeight(600);

    QVBoxLayout *  vlayout = new QVBoxLayout(mainWidget);
    vlayout->addWidget(trainstationList);

    goodSelector = new GoodSelector();
    connect(goodSelector, &GoodSelector::addWagonClicked, this, &RouteInterface::addWagon);
    vlayout->addWidget(goodSelector);

    routeName = new QLineEdit;
    routeName->setMaximumWidth(220);
    routeName->setText("Routenname eingeben");
    vlayout->addWidget(routeName);

    QHBoxLayout * buttons = new QHBoxLayout(mainWidget);
    QPushButton * confirmBtn = new QPushButton("Bestätigen");
    confirmBtn->setCursor(QCursor(Qt::PointingHandCursor));
    confirmBtn->setIcon(QIcon(":/icons/checkmark.svg"));
    connect(confirmBtn, &QPushButton::clicked, this, &RouteInterface::confirmRoute); //Bestätige Route
    buttons->addWidget(confirmBtn);


    QPushButton * cancelBtn = new QPushButton("Abbrechen");
    cancelBtn->setCursor(QCursor(Qt::PointingHandCursor));
    cancelBtn->setIcon(QIcon(":/icons/cross.svg"));
    connect(cancelBtn, SIGNAL (clicked()), this, SLOT (toggle())); //schließe RouteInterface
    buttons->addWidget(cancelBtn);

    vlayout->addLayout(buttons);
    layout->addLayout(vlayout);

    mainWidget->setLayout(layout);

    QDockWidget::setWidget(mainWidget);
    mainWidget->setStyleSheet("background-color:rgb(150,150,255)");

    wagonCount = 0;
    tsCount = 0;
}

/**
 * @brief RouteInterface::toggle Wechselt die Sichtbarkeit des Widgets.
 */
void RouteInterface::toggle() {
    if (this->isVisible()) {
        //Entferne Waggons, wenn Interface geschlossen wird
        trainstationList->clear();
        trainRenderer->deleteAllWagons();
    }
    QDockWidget::setVisible(!QDockWidget::isVisible());
    qDebug() << this->isVisible();
    wagonCount = 0;
    tsCount = 0;
}

/**
 * @brief RouteInterface::onTileInteract Wird ausgeführt wenn ein Bahnhof angeklickt wurde.
 */
void RouteInterface::onTileInteract(int px, int py, int type)
{
    if(QWidget::isVisible()){
        switch(type){
            case MapTile::TERMINAL_H:
            case MapTile::TERMINAL_V:
            case MapTile::STATION_H:
            case MapTile::STATION_V:
            case MapTile::DEPOT_H:
            case MapTile::DEPOT_V:
                tsCoords[tsCount] = QPoint(px,py);  //Koordinaten jeder Trainstation werden gespeichert
                tsCount++;  //Anzahl Trainstations erhöht
                QListWidgetItem *newItem = new QListWidgetItem(QIcon(":/images/depot.png"), "Bahnhof " + QString::number(px) + "/" + QString::number(py));
                this->trainstationList->addItem(newItem);
                break;
        }

    }
}

/**
 * @brief RouteInterface::addWagon Slot zum hinzufügen eines Wagons zum aktuellen Renderer.
 * @param name Der Name des Wagons.
 */
void RouteInterface::addWagon(QString * name)
{
    if (wagonCount < 10) {
            trainRenderer->addWagon(name->toStdString());
            wagonCount++;
        }
        else {
            qDebug() << "Zu viele Waggons! " << wagonCount;
        }
}

/**
 * @brief RouteInterface::confirmRoute Sendet dem Server die Informationen der erstellten Route in Form eines Strings, sodass dieser die Route auf dem Server erzeugen kann.
 */
void RouteInterface::confirmRoute()
{
    QString handOver = "ROUTE";

    for (int i=0; i < tsCount; i++) {
        handOver += " TS " + QString::number(tsCoords[i].x()) + " " + QString::number(tsCoords[i].y());  //TS ist das Stichwort für den Server um Trainstation Koordinaten zu empfangen
    }

    handOver += " WAGONS";  //WAGONS ist das Stichwort für den Server um die Waggons zu empfangen

    for (std::pair<std::string, int> wagon : trainRenderer->wagons){
        for(int i = 0; i<wagon.second; i++){
            handOver += " " + QString::fromStdString(wagon.first);
        }
    }
    handOver += " " + routeName->text().replace(" ", "");
    handOver += "~";
    emit sendConfirmRoute(handOver);
    this->toggle();
}

/**
 * @brief RouteInterface::removeWagon Zählt die Anzahl der aktuell angehängten Waggons herunter.
 */
void RouteInterface::removeWagon() {
    wagonCount--;
    qDebug() << "Waggon gelöscht - Anzahl: " << wagonCount;
}
