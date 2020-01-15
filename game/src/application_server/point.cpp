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

/**
 * @brief Point::add Addiert Werte auf den Punkt.
 * @return Ein neuer Punkt.
 */
Point Point::add(int ax, int ay)
{
    return Point(x+ax, y+ay);
}

/**
 * @brief Point::set Ändert die Koordinaten.
 */
void Point::set(int nx, int ny)
{
    x = nx;
    y = ny;
}

/**
 * @brief Point::move Verschiebt den Punkt.
 */
void Point::move(int mx, int my)
{
    x += mx;
    y += my;
}

/**
 * @brief Point::toTile Gibt den Punkt als Tile-Index zurück.
 * @return Ein neuer Punkt.
 */
Point Point::toTile()
{
    return Point(x/64, y/64);
}
