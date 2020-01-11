#include "point.h"

/**
 * @brief Point::Point Erzeugt einen 2D-Punkt.
 * @param pX Die X-Koordinate.
 * @param pY Die Y-Koordinate.
 */
Point::Point(int pX, int pY):
    x{pX},y{pY}
{}

/**
 * @brief Point::getX Gibt die X-Koordinate des Punktes.
 * @return Die X-Koordinate.
 */
int Point::getX(){return x;}

/**
 * @brief Point::getX Gibt die Y-Koordinate des Punktes.
 * @return Die Y-Koordinate.
 */
int Point::getY(){return y;}
