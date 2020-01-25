#include "routelistinterface.h"

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
    routeList->setSelectionMode(QAbstractItemView::SingleSelection);  //mehrere Elemente der Liste gleichzeitig anwählbar mit STRG

    routeList->setMaximumHeight(600);

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
    routeList->clear(); //Lösche vorher gespeicherte Elemente der Liste
    emit sendRequestRoutes();   //Fragt beim Server nach einer Liste aller Routen, die dieser Spieler aktuell am Laufen hat
    QDockWidget::setVisible(!QDockWidget::isVisible());
    qDebug() << this->isVisible();
}

/**
 * @brief RouteListInterface::deleteRoute Sendet ein Signal, sodass die Route des Sielers vom Server gelöscht wird.
 */
void RouteListInterface::deleteRoute() {

    if (routeList->count() != 0) {
        qDebug() << "Items werden gelöscht...";

        qDebug() << routeList;

        emit sendDeleteSignal(routeList->takeItem(routeList->currentRow()));
        delete routeList->takeItem(routeList->currentRow());

        qDebug() << "WURDE GELÖSCHT";
    }
    else {
        qDebug() << "Keine Route zum Löschen ausgewählt.";
    }

}

/**
 * @brief RouteListInterface::receiveRoutes Formatiert die Liste aus Strings zu schöneren einzelnen Strings, die mit dem QListWidget routeList im Interface dargestellt werden.
 * @param routeStringList die Liste der empfangenen Routen in Form von Strings
 */
void RouteListInterface::receiveRoutes(QStringList * routeStringList) {
    QString routeString = routeStringList->at(1) + ": ";
    bool wagonsReceived = false;
    int coordCount = 0;
    QRegExp re("\\d*"); //Eine Nummer, beliebig viele Stellen

    for (int i=2; i < routeStringList->length(); i++) {
        qDebug() << "Schleifendurchlauf " << i;

        if ( routeStringList->at(i) == "COAL" ||
             routeStringList->at(i) == "FOOD" ||
             routeStringList->at(i) == "LIVESTOCK" ||
             routeStringList->at(i) == "WOOD" ||
             routeStringList->at(i) == "CORN" ||
             routeStringList->at(i) == "GOODS" ||
             routeStringList->at(i) == "PAPER" ||
             routeStringList->at(i) == "MAIL" ||
             routeStringList->at(i) == "PASSENGERS" ) {

            if (wagonsReceived == false) {
                routeString += "- Angehängte Waggons: ";
            }
            else {
                routeString += ", ";
            }
            wagonsReceived = true;
        }
        else if ( re.exactMatch(routeStringList->at(i)) ) {
            coordCount++;
        }

        if ( (wagonsReceived && re.exactMatch(routeStringList->at(i))) || routeStringList->at(i) == "END") {
            qDebug() << "Vollständige Route empfangen";
            routeList->addItem(routeString);
            wagonsReceived = false;
            routeString = "";
            coordCount = 0;
        }

        if (routeStringList->at(i) != "ROUTES" && routeStringList->at(i) != "END") {
            routeString += routeStringList->at(i);
        }

        if (coordCount%2 == 0 && wagonsReceived == false) {
            routeString += ", ";
        }
        else if (coordCount%2 == 1) {
            routeString += "/";
        }
    }
}

