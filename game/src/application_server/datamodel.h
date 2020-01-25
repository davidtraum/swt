#ifndef DATAMODEL_H
#define DATAMODEL_H

#include <QLabel>
#include <QWidget>
#include <QString>
#include <QMediaPlayer>
#include <QVideoWidget>


#include "mainwindow.h"
#include "player.h"
#include "infowidget.h"

class DataModel: public QObject
{
    Q_OBJECT
public:
    DataModel(MainWindow *);
    int getBalance();
    void updateBalance(int pBalance);
    bool takeBalance(int pAmount);
    void timeTick();
    long getTime();
    void setTime(long);
    long getSystemMillis();
    void updateCoordinates(int pX, int pY);
    int getHoverX();
    int getHoverY();
    void toggleFullscreen();
    QString formatTime(long pTime);
    QString getFormattedTime();
    void setConnectionInfo(QString pString);
    QString * getIP();
    quint16 getPort();
    void setGuiBalanceLabel(QLabel * label);
    void setGuiTimeLabel(QLabel * label);
    void setGuiPositionLabel(QLabel * label);
    void setStatusDisplayLabel(QLabel * label);
    void setConnectionLabel(QLabel * label);
    void setInfoWidget(InfoWidget * widget);
    InfoWidget * getInfoWidget();
    enum MODE{DEFAULT,
              TRAIN_STATION,
              TRAIN_DEPOT,
              TRAIN_TERMINAL,
              BRIDGE,
              RAIL_PLACEMENT,
              REMOVE};
    void setMode(MODE);
    MODE getMode();
    Player * secondPlayer;
    const int RADIUS_DEPOT = 1*64;
    const int RADIUS_STATION = 2*64;
    const int RADIUS_TERMINAL = 3*64;
    static bool mapLoaded;
    MainWindow * mainWindow;

private:
    int balance;
    long time;
    int coordinateX,coordinateY;
    QString ip;
    QString timeString;
    quint16 port;
    QLabel * balanceLabel;
    QLabel * timeLabel;
    QLabel * positionLabel;
    QLabel * statusDisplay;
    QLabel * connectionLabel;
    InfoWidget * infoWidget;

    MODE mode{MODE::DEFAULT};

signals:
    void positionChange(int,int);
    void viewChange();
public slots:
    void setDefaultMode();
    void setTrainStationMode();
    void setDepotMode();
    void setTerminalMode();
    void setBridgeMode();
    void setRailPlacementMode();
    void setRemoveMode();
    void setMapLoaded(bool);
};

#endif // DATAMODEL_H
