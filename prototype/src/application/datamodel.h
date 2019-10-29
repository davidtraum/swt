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
private:
    int balance;
    QLabel * balanceLabel;
};

#endif // DATAMODEL_H
