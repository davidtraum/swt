#include "routeinterface.h"

#include <QCursor>
#include <QDebug>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QGroupBox>
#include <QString>


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
}

/**
 * @brief RouteInterface::trainStationSelected Wird ausgeführt wenn ein Bahnhof angeklickt wurde.
 */
void RouteInterface::trainStationSelected(int px, int py)
{
    if(QWidget::isVisible()){
        qDebug() << "Selected " << px << " " << py;
        QListWidgetItem *newItem = new QListWidgetItem(QIcon(":/images/depot.png"), "Bahnhof " + QString::number(px) + "/" + QString::number(py));
        this->trainstationList->addItem(newItem);
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

void RouteInterface::confirmRoute()
{
    QString handOver = "ROUTE";
    for (std::pair<std::string, int> wagon : trainRenderer->wagons){
        for(int i = 0; i<wagon.second; i++){
            handOver += " " + QString::fromStdString(wagon.first);
        }
    }
    handOver += "~";
    emit sendConfirmRoute(handOver);
}

void RouteInterface::removeWagon() {
    wagonCount--;
    qDebug() << "Waggon gelöscht - Anzahl: " << wagonCount;
}
