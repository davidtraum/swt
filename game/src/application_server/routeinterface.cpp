#include "routeinterface.h"

#include <QCursor>
#include <QDebug>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>

/**
 * @brief RouteInterface::RouteInterface Erzeugt das Routeninterface.
 */
RouteInterface::RouteInterface(GraphicsManager * gm)
{
    QDockWidget::setFeatures(nullptr);
    QDockWidget::setVisible(false);

    QWidget * mainWidget = new QWidget();

    QHBoxLayout * layout = new QHBoxLayout(mainWidget);

    trainRenderer = new TrainRenderer(gm);
    layout->addWidget(trainRenderer);

    trainstationList = new QListWidget();
    trainstationList->setFixedWidth(200);

    QVBoxLayout *  vlayout = new QVBoxLayout(mainWidget);
    vlayout->addWidget(trainstationList);

    QPushButton * confirmBtn = new QPushButton("Bestätigen");
    confirmBtn->setCursor(QCursor(Qt::PointingHandCursor));
    confirmBtn->setIcon(QIcon(":/icons/checkmark.svg"));
    vlayout->addWidget(confirmBtn);

    layout->addLayout(vlayout);

    mainWidget->setLayout(layout);

    QDockWidget::setWidget(mainWidget);
}

/**
 * @brief RouteInterface::toggle Wechselt die Sichtbarkeit des Widgets.
 */
void RouteInterface::toggle() {
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

