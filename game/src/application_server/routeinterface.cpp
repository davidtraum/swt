#include "routeinterface.h"

#include <QCursor>
#include <QDebug>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QGroupBox>


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
}

/**
 * @brief RouteInterface::toggle Wechselt die Sichtbarkeit des Widgets.
 */
void RouteInterface::toggle() {
    if (this->isVisible()) {
        //Entferne Waggons, wenn Interface geschlossen wird
        trainRenderer->deleteAllWagons();
    }
    QDockWidget::setVisible(!QDockWidget::isVisible());
    qDebug() << this->isVisible();
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
    trainRenderer->addWagon(name->toStdString());
}


