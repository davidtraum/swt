#include "menubar.h"
#include <QDebug>
#include "client.h"
#include "datamodel.h"
#include <QIcon>
#include <QTimer>

/**
 * @brief MenuBar::MenuBar Erzeugt Menüstruktur.
 */
MenuBar::MenuBar(Scene * pScene, DataModel * pDataModel, View * pView) :
    scene{pScene}, dataModel{pDataModel}, view{pView}
{
    QMenu * mainMenu = QMenuBar::addMenu("Spiel");
    QMenu * serverSelection = mainMenu->addMenu(QIcon(":/icons/server.svg"), "Serververbindung");
    QAction * openConnection = serverSelection->addAction(QIcon(":/icons/verbindungsaufbau.svg"), "Verbindungsaufbau");
    QAction * closeConnection = serverSelection->addAction(QIcon(":/icons/verbindungstrennung.svg"), "Verbindung trennen");
    connect(openConnection, &QAction::triggered, this, &MenuBar::slotOpenConnection);
    connect(closeConnection, &QAction::triggered, this, &MenuBar::slotCloseConnection);
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
                                         "traum.me:2000",
                                         &ok);

    if(ok){
        Client * client = new Client(&text, scene, view, dataModel);

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
