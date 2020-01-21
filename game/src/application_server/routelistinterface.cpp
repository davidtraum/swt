#include "routeListInterface.h"

#include <QGroupBox>
#include <QHBoxLayout>
#include <QDebug>

RouteListInterface::RouteListInterface()
{

    QDockWidget::setFeatures(nullptr);
    QDockWidget::setVisible(false);

    QGroupBox * mainWidget = new QGroupBox(" Routen verwalten");

    QVBoxLayout * layout = new QVBoxLayout(mainWidget);

    routeList = new QListWidget();
    routeList->setSelectionMode(QAbstractItemView::ExtendedSelection);  //mehrere Elemente der Liste gleichzeitig anwählbar mit STRG

    routeList->setMaximumHeight(600);
    routeList->addItem("Beispielroute 1: Vom Ring bis an die Wolga, 8 Stationen -- Angehängte Waggons: Kohle, Kohle, Weizen, Passagiere");
    routeList->addItem("Beispielroute 2: Durch den Monsun, 3 Stationen -- Angehängte Waggons: Passagiere, Kohle, Weizen, Partyartikel");

    layout->addWidget(routeList);

    QHBoxLayout * buttons = new QHBoxLayout(mainWidget);
    QPushButton * deleteBtn = new QPushButton("gewählte Route löschen");
    connect(deleteBtn, &QPushButton::clicked, this, &RouteListInterface::deleteRoute);
    buttons->setAlignment(Qt::AlignBottom);
    buttons->addWidget(deleteBtn);


    QPushButton * cancelBtn = new QPushButton("Abbrechen");
    cancelBtn->setCursor(QCursor(Qt::PointingHandCursor));
    cancelBtn->setIcon(QIcon(":/icons/cross.svg"));
    connect(cancelBtn, &QPushButton::clicked, this, &RouteListInterface::toggle); //schließe RouteListInterface
    buttons->addWidget(cancelBtn);

    layout->addLayout(buttons);
    layout->setAlignment(Qt::AlignBottom);

    mainWidget->setLayout(layout);

    QDockWidget::setWidget(mainWidget);
    mainWidget->setStyleSheet("background-color:rgb(150,150,255)");

}

/**
 * @brief RouteListInterface::toggle Wechselt die Sichtbarkeit des Widgets.
 */
void RouteListInterface::toggle() {
    qDebug() << "RouteListInterface toggled";
    emit sendRequestRoutes();   //Fragt beim Server nach einer Liste aller Routen, die dieser Spieler aktuell am Laufen hat
    QDockWidget::setVisible(!QDockWidget::isVisible());
    qDebug() << this->isVisible();
}

void RouteListInterface::deleteRoute() {

    qDebug() << "Items werden gelöscht...";

    qDebug() << routeList;
    delete routeList->takeItem(routeList->currentRow());
    qDebug() << "WURDE GELÖSCHT";

}

