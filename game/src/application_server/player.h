#ifndef PLAYER_H
#define PLAYER_H

#include "highlighter.h"

class Player
{
public:
    Player();
    Highlighter * highlighter;
    int posX,posY;
    void setPosition(int pX, int pY);
};

#endif // PLAYER_H
