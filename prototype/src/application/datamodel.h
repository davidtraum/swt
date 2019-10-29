#ifndef DATAMODEL_H
#define DATAMODEL_H

#include <QLabel>

class DataModel
{
public:
    DataModel();
    int getBalance();
    void updateBalance(int pBalance);
    void setGuiBalanceLabel(QLabel * label);
    void setGuiTimeLabel(QLabel * label);
    void timeTick();
    long getTime();
private:
    int balance;
    long time;
    QLabel * balanceLabel;
    QLabel * timeLabel;
};

#endif // DATAMODEL_H
