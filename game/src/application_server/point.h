#ifndef POINT_H
#define POINT_H


class Point
{
public:
    Point(int,int);
    int getX();
    int getY();
    Point add(int,int);
    void set(int,int);
    void move(int,int);
    Point toTile();
private:
    int x,y;
};

#endif // POINT_H
