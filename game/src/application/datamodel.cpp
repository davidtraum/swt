#include "datamodel.h"

/**
 * @brief DataModel::DataModel Diese Klasse verwaltet alle globalen Daten rund um den Spielverlauf, z.B. den Kontostand.
 */
DataModel::DataModel()
{
    balance = 2000;
    time = 0;
    coordinateX = 150;
    coordinateY = 150;
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
    balanceLabel->setText("<img height=\"32\" src=\":/icons/cash.svg\"></img> <h2>" + QString::fromStdString(std::to_string(balance)) + "$</h2>");
}

/**
 * @brief DataModel::takeBalance Zieht Geld ab falls noch genug da ist.
 * @param pAmount Die Geldzahl zum Entfernen.
 * @return true wenn genug Geld da war und entfernt wurde. false wenn nicht genug Geld da ist.
 */
bool DataModel::takeBalance(int pAmount){
    if(balance>=pAmount){
        updateBalance(balance-pAmount);
        return true;
    }else{
        return false;
    }
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
    timeLabel->setText("<img height=\"32\" src=\":/icons/clock.svg\"></img> <h2>" + QString::fromStdString(formatTime(time)) + "</h2>");
}

/**
 * @brief DataModel::formatTime Formattiert einen Timecode als String.
 * @param pTime Der Timecode.
 * @return Der Text.
 */
std::string DataModel::formatTime(long pTime){
    long hrs = pTime / 1000;
    long mins = long(((pTime % 1000) / 1000.0)*60);
    return "Tag " + std::to_string((hrs/24)+1) + "<br>" + std::to_string(hrs) + ":" + (mins < 10 ? "0" + std::to_string(mins) : std::to_string(mins))  + "h";
}

/**
 * @brief DataModel::updateCoordinates Aktualisiert die Koordinaten des fokussierten Quadrantens.
 * @param pX Die X Koordinate.
 * @param pY Die Y Koordinate.
 */
void DataModel::updateCoordinates(int pX, int pY){
    coordinateX = pX;
    coordinateY = pY;
    positionLabel->setText(QString::fromStdString("<img height=\"32\" src=\":/icons/location.svg\"></img><h2>X: " + std::to_string(pX) + "<br>Y: " + std::to_string(pY)));
}

/**
 * @brief DataModel::getSystemMillis Gibt die Zahl der Millisekunden seit 1970 zurück.
 * @return Die Zahl der Millisekunden.
 */
long DataModel::getSystemMillis(){
     return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
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

/**
 * @brief DataModel::setGuiTimeLabel Setzt das Label in welchem die Koordinate dargestellt wird.
 * @param label Ein Pointer auf ein QLabel Objekt.
 */
void DataModel::setGuiPositionLabel(QLabel *label){
    positionLabel = label;
    updateCoordinates(coordinateX, coordinateY);
}
