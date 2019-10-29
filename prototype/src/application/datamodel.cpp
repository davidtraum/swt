#include "datamodel.h"

/**
 * @brief DataModel::DataModel Diese Klasse verwaltet alle globalen Daten rund um den Spielverlauf, z.B. den Kontostand.
 */
DataModel::DataModel()
{
    balance = 2000;
    time = 0;
}

/**
 * @brief DataModel::getBalance Liefert den aktuellen Kontostand zurück.
 * @return Der aktuelle Kontostand.
 */
int DataModel::getBalance()
{
    return balance;
}

/**
 * @brief DataModel::updateBalance Aktualisiert den Kontostand. Auch in Anzeigen etc.
 * @param pBalance Der neue Kontostand.
 */
void DataModel::updateBalance(int pBalance)
{
    balance = pBalance;
    balanceLabel->setText("Kontostand: " + QString::fromStdString(std::to_string(balance)));
}

/**
 * @brief DataModel::getTime Liefert die aktuelle Zeit als Timecode. (Zahl die je nach Geschwindigkeit wächst)
 * @return Der Timecode.
 */
long DataModel::getTime(){
    return time;
}

/**
 * @brief DataModel::timeTick Wird aufgerufen wenn eine Zeiteinheit verstrichen ist. Erhöht den Timecode.
 */
void DataModel::timeTick(){
    time++;
    timeLabel->setText("Zeit: " + QString::fromStdString(std::to_string(time)));
}

/**
 * @brief DataModel::setGuiBalanceLabel Setzt das Label in welchem der Kontostand dargestellt wird.
 * @param label Ein Pointer auf ein QLabel Objekt.
 */
void DataModel::setGuiBalanceLabel(QLabel *label){
    balanceLabel = label;
    updateBalance(balance);
}

/**
 * @brief DataModel::setGuiTimeLabel Setzt das Label in welchem die Zeit dargestellt wird.
 * @param label Ein Pointer auf ein QLabel Objekt.
 */
void DataModel::setGuiTimeLabel(QLabel *label){
    timeLabel = label;
    timeTick();
}
