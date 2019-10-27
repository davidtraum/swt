#ifndef CITY_H
#define CITY_H

#include <string>

class City
{
public:
    City(int pX, int pY, int pSize);
    City();
    int getSize();
    int getCenterX();
    int getCenterY();
    std::string getName();
    void setSize(int pSize);
    void setCenter(int pX, int pY);
    void setName(std::string pName);

private:
    int size;
    int centerX,centerY;
    std::string name;
};

#endif // CITY_H
