#ifndef DATAMODEL_H
#define DATAMODEL_H

#include <string>
#include <QLabel>
#include <QWidget>

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
    enum MODE{DEFAULT,
              TRAIN_STATION,
              BRIDGE,
              RAIL_PLACEMENT};
    void setMode(MODE);
    MODE getMode();

private:
    int balance;
    long time;
    int coordinateX,coordinateY;
    QString ip;
    quint16 port;
    QLabel * balanceLabel;
    QLabel * timeLabel;
    QLabel * positionLabel;
    QLabel * statusDisplay;
    MODE mode{MODE::DEFAULT};

signals:
    void positionChange(int,int);
    void viewChange();
public slots:
    void setDefaultMode();
    void setTrainStationMode();
    void setBridgeMode();
    void setRailPlacementMode();
};

#endif // DATAMODEL_H
