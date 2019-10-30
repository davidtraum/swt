#ifndef DATAMODEL_H
#define DATAMODEL_H

#include <string>
#include <QLabel>

class DataModel
{
public:
    DataModel();
    int getBalance();
    void updateBalance(int pBalance);
    void timeTick();
    long getTime();
    void updateCoordinates(int pX, int pY);
    std::string formatTime(long pTime);

    void setGuiBalanceLabel(QLabel * label);
    void setGuiTimeLabel(QLabel * label);
    void setGuiPositionLabel(QLabel * label);
private:
    int balance;
    long time;
    int coordinateX,coordinateY;
    QLabel * balanceLabel;
    QLabel * timeLabel;
    QLabel * positionLabel;
};

#endif // DATAMODEL_H
