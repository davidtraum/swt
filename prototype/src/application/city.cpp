#include "city.h"

/**
 * @brief City::City Erzeugt eine Stadt mit vorgegebenen Parametern.
 * @param pX Der X-Index des Mittelpunktes.
 * @param pY Der Y-Index des Mittelpunktes.
 * @param pSize Die größe der Stadt.
 */
City::City(int pX, int pY, int pSize)
{
    centerX = pX;
    centerY = pY;
    size = pSize;
    name = "Teststadt";
}

/**
 * @brief City::City Erzeugt eine leere Stadt.
 */

City::City(){
    name = "Teststadt";
}

/**
 * @brief City::getSize Gibt die Anzahl der Felder zurück die zur Stadt gehören.
 * @return Die Größe.
 */
int City::getSize(){
    return size;
}

/**
 * @brief City::getCenterX
 * @return Die X Koordinate des Mittelpunktes der Stadt.
 */
int City::getCenterX(){
    return centerX;
}

/**
 * @brief City::getCenterY
 * @return Die Y Koordinate des Mittelpunktes der Stadt.
 */
int City::getCenterY(){
    return centerY;
}

/**
 * @brief City::setSize Gibt die Größe der Stadt zurück (Anzahl der Gebäude)
 * @param pSize Die Größe der Stadt
 */
void City::setSize(int pSize){
    size = pSize;
}

/**
 * @brief City::setCenter Setzt den Mittelpunkt der Stadt.
 * @param pX Der X-Index.
 * @param pY Der Y-Index.
 */
void City::setCenter(int pX, int pY){
    centerX = pX;
    centerY = pY;
}

/**
 * @brief City::getName Gibt den Namen der Stadt.
 * @return Der Name der Stadt.
 */
std::string City::getName(){
    return name;
}

/**
 * @brief City::setName Setzt den Namen der Stadt.
 * @param pName Der neue Name.
 */
void City::setName(std::string pName){
    name = pName;
}
