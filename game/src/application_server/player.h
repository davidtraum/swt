#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsRectItem>

class Player
{
public:
    Player(int pId);
    QGraphicsRectItem * highlighter;
    int posX,posY;
    void setPosition(int pX, int pY);
};

#endif // PLAYER_H
