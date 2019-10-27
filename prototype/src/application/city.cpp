#include "city.h"

City::City(int pX, int pY, int pSize)
{
    centerX = pX;
    centerY = pY;
    size = pSize;
    name = "Teststadt";
}

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
 * @brief City::setSize
 * @param pSize Die Größe der Stadt
 */
void City::setSize(int pSize){
    size = pSize;
}

/**
 * @brief City::setCenter
 * @param pX
 * @param pY
 */
void City::setCenter(int pX, int pY){
    centerX = pX;
    centerY = pY;
}

std::string City::getName(){
    return name;
}

void City::setName(std::string pName){
    name = pName;
}
