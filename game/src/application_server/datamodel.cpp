#include "datamodel.h"
#include <QDebug>


bool DataModel::mapLoaded = false;

/**
 * @brief DataModel::DataModel Diese Klasse verwaltet alle globalen Daten rund um den Spielverlauf, z.B. den Kontostand.
 */
DataModel::DataModel(MainWindow * pMainWindow):
    mainWindow{pMainWindow}
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
 * @brief DataModel::setTime Setzt den aktuellen Zeitstempel
 */
void DataModel::setTime(long pTime)
{
    time = pTime;
}

/**
 * @brief DataModel::timeTick Wird aufgerufen wenn eine Zeiteinheit verstrichen ist. Erhöht den Timecode.
 */
void DataModel::timeTick(){
    time++;
    timeString = formatTime(time);
    //timeLabel->setText("<img height=\"32\" src=\":/icons/clock.svg\"></img> <h2>" + QString::fromStdString(formatTime(time)) + "</h2>");
}

/**
 * @brief DataModel::formatTime Formattiert einen Timecode als String.
 * @param pTime Der Timecode.
 * @return Der Text.
 */
QString DataModel::formatTime(long pTime){
    long hrs = pTime / 1000;
    long mins = long(((pTime % 1000) / 1000.0)*60);
    return QString("Tag " + QString::number((hrs/24)+1) + ", " +  QString::number(hrs) + ":" + (mins < 10 ? "0" + QString::number(mins) : QString::number(mins))  + "h");
}

/**
 * @brief DataModel::getFormattedTime Liefert die gecachte formatierte Zeit zurück.
 * @return Ein QString.
 */
QString DataModel::getFormattedTime()
{
    return timeString;
}

/**
 * @brief DataModel::updateCoordinates Aktualisiert die Koordinaten des fokussierten Quadrantens.
 * @param pX Die X Koordinate.
 * @param pY Die Y Koordinate.
 */
void DataModel::updateCoordinates(int pX, int pY){
    if(pX!=coordinateX || pY!=coordinateY){
        if(mapLoaded){
            emit positionChange(pX,pY);
        }
    }
    coordinateX = pX;
    coordinateY = pY;
    //positionLabel->setText(QString::fromStdString("<img height=\"32\" src=\":/icons/location.svg\"></img><h2>X: " + std::to_string(pX) + "<br>Y: " + std::to_string(pY)));
}

/**
 * @brief DataModel::getHoverX Gibt die aktuelle Koordinate der Kachel zurück über der die Maus ist.
 * @return Eine Kachel-Koordinate.
 */
int DataModel::getHoverX()
{
    return coordinateX;
}

/**
 * @brief DataModel::getHoverX Gibt die aktuelle Koordinate der Kachel zurück über der die Maus ist.
 * @return Eine Kachel-Koordinate.
 */
int DataModel::getHoverY()
{
    return coordinateY;
}

/**
 * @brief DataModel::toggleFullscreen Toggled den Vollbildmodus.
 */
void DataModel::toggleFullscreen()
{
    if(mainWindow->isFullScreen()){
        mainWindow->showNormal();
    }else{
        mainWindow->showFullScreen();
    }
}


/**
 * @brief DataModel::getSystemMillis Gibt die Zahl der Millsekunden seit 1970 zurück.
 * @return Die Zahl der Millisekunden.
 */
long DataModel::getSystemMillis(){
     return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}


/**
 * @brief DataModel::setConnectionInfo Setzt die Verbindungsinformation als String.
 * @param pString Die IP und der Port im Format IP:PORT
 */
void DataModel::setConnectionInfo(QString pString){
    QStringList split = pString.split(":");
    ip = split[0];
    port = quint16(split[1].toInt());
    //connectionLabel->setText("<img height=\"12\" src=\":icons/server.svg\"> " + ip);
}

/**
 * @brief DataModel::getIP Gibt die IP Adresse zur Verbindung zurück.
 * @return Die IP Adresse als QString
 */
QString * DataModel::getIP(){
    return &ip;
}

/**
 * @brief DataModel::getPort Gibt den Port zur Verbindung zurück.
 * @return Der Port als int.
 */
quint16 DataModel::getPort(){
    return port;
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


/**
 * @brief DataModel::setStatusDisplayLabel Setzt das Label in dem der aktuelle Bearbeitungsmodus angezeigt wird.
 * @param label Ein Pointer auf ein QLabel Objekt.
 */
void DataModel::setStatusDisplayLabel(QLabel *label){
    statusDisplay = label;
}

/**
 * @brief DataModel::setStatusDisplayLabel Setzt das Label in dem der aktuelle Bearbeitungsmodus angezeigt wird.
 * @param label Ein Pointer auf ein QLabel Objekt.
 */
void DataModel::setConnectionLabel(QLabel *label)
{
    connectionLabel = label;
}

/**
 * @brief DataModel::setInfoWidget Setzt das Info Widget
 * @param widget Das Info Widget.
 */
void DataModel::setInfoWidget(InfoWidget *widget)
{
    infoWidget = widget;
}

/**
 * @brief DataModel::getInfoWidget Liefet das gespeicherte Info Widget.
 * @return Das Info Widget.
 */
InfoWidget *DataModel::getInfoWidget()
{
    return infoWidget;
}

/**
 * @brief DataModel::setMode Setzt den aktuellen Bearbeitungsmodus.
 * @param pMode Bearbeitungsmodus.
 */
void DataModel::setMode(DataModel::MODE pMode){
    mode = pMode;
    switch(mode){
        case DataModel::TRAIN_STATION:
            statusDisplay->setText("<h2>Bahnhof bauen</h2>");
            break;
        case DataModel::TRAIN_DEPOT:
            statusDisplay->setText("<h2>Depot bauen</h2>");
            break;
        case DataModel::TRAIN_TERMINAL:
            statusDisplay->setText("<h2>Terminal bauen</h2>");
            break;
        case DataModel::BRIDGE:
            statusDisplay->setText("<h2>Brücke bauen</h2>");
            break;
        case DataModel::RAIL_PLACEMENT:
            statusDisplay->setText("<h2>Schienen platzieren</h2>");
            break;
        case DataModel::REMOVE:
            statusDisplay->setText("<h2>Entferne</h2>");
            break;
        default:
            statusDisplay->setText("");
            break;
    }
}

/**
 * @brief DataModel::setDefaultMode Signal um in den Standard Bearbeitungsmodus zu wechseln.
 */
void DataModel::setDefaultMode(){
    setMode(DataModel::MODE::DEFAULT);
}

/**
 * @brief DataModel::setRailPlacementMode Signal um in den Bahnhofseditor zu wechseln.
 */
void DataModel::setTrainStationMode(){
    setMode(DataModel::MODE::TRAIN_STATION);
}

/**
 * @brief DataModel::setRailPlacementMode Signal um in den Bahnhofseditor zu wechseln.
 */
void DataModel::setDepotMode(){
    setMode(DataModel::MODE::TRAIN_DEPOT);
}


/**
 * @brief DataModel::setRailPlacementMode Signal um in den Bahnhofseditor zu wechseln.
 */
void DataModel::setTerminalMode(){
    qDebug() << "Terminal";
    setMode(DataModel::MODE::TRAIN_TERMINAL);
}


/**
 * @brief DataModel::setRailPlacementMode Signal um in den Brückeneditor zu wechseln.
 */
void DataModel::setBridgeMode(){
    setMode(DataModel::MODE::BRIDGE);
}

/**
 * @brief DataModel::setRailPlacementMode Signal um in den Gleiseditor zu wechseln.
 */
void DataModel::setRailPlacementMode(){
    setMode(DataModel::MODE::RAIL_PLACEMENT);
}
/**
* @brief DataModel::setRailPlacementMode Signal um in den Removeeditor zu wechseln.
*/
void DataModel::setRemoveMode(){
    setMode(DataModel::MODE::REMOVE);
}
/**
 * @brief DataModel::setMapLoaded Setzt das die Karte geladen wurde.
 */
void DataModel::setMapLoaded(bool status)
{
    mapLoaded = status;
    emit viewChange();
}

/**
 * @brief DataModel::getMode Gibt den aktuellen Bearbeitungsmodus
 * @return Der aktuelle Modus.
 */
DataModel::MODE DataModel::getMode(){
    return mode;
}

