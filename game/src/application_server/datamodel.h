#ifndef DATAMODEL_H
#define DATAMODEL_H

#include <string>
#include <QLabel>
#include <QWidget>

#include "player.h"
#include "animationmanager.h"

class DataModel: public QObject
{
    Q_OBJECT
public:
    DataModel();
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
    std::string formatTime(long pTime);
    void setConnectionInfo(QString pString);
    QString * getIP();
    quint16 getPort();
    void setGuiBalanceLabel(QLabel * label);
    void setGuiTimeLabel(QLabel * label);
    void setGuiPositionLabel(QLabel * label);
    void setStatusDisplayLabel(QLabel * label);
    void setConnectionLabel(QLabel * label);
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
    void setAnimationManager(AnimationManager *);
    AnimationManager * getAnimationManager();

private:
    int balance;
    long time;
    int coordinateX,coordinateY;
    bool mapLoaded{false};
    QString ip;
    quint16 port;
    QLabel * balanceLabel;
    QLabel * timeLabel;
    QLabel * positionLabel;
    QLabel * statusDisplay;
    QLabel * connectionLabel;
    MODE mode{MODE::DEFAULT};
    AnimationManager * animationManager;

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
