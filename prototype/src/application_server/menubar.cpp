#include "menubar.h"
#include <QDebug>
#include "client.h"
#include "datamodel.h"

/**
 * @brief MenuBar::MenuBar Erzeugt Menüstruktur.
 */
MenuBar::MenuBar(Scene * pScene) :
    scene{pScene}
{
    QMenu * mainMenu = QMenuBar::addMenu("Spiel");
    QMenu * serverSelection = mainMenu->addMenu("Serververbindung");
    QAction * openConnection = serverSelection->addAction("Verbindungsaufbau");
    QAction * closeConnection = serverSelection->addAction("Verbindung trennen");
    connect(openConnection, &QAction::triggered, this, &MenuBar::slotOpenConnection);
    connect(closeConnection, &QAction::triggered, this, &MenuBar::slotCloseConnection);
}

/**
 * @brief MenuBar::openConnection
 */
void MenuBar::slotOpenConnection(){

    bool ok;
    QString text = QInputDialog::getText(nullptr,
                                         "Serververbindung",
                                         "IP-Adresse",
                                         QLineEdit::Normal,
                                         "traum.me:2000",
                                         &ok);

    Client * client = new Client(&text, scene);

}

/**
 * @brief MenuBar::closeConnection
 */
void MenuBar::slotCloseConnection()
{
    qDebug()<<"close";
}
