#include "player.h"

#include <QPen>
Player::Player()
{
    highlighter = new Highlighter();

    posX = 0;
    posY = 0;
}

/**
 * @brief Player::setPosition Updated die Position des Spielers.
 * @param pX Der X-Index
 * @param pY Der Y-Index
 */
void Player::setPosition(int pX, int pY){
    posX=pX;
    posY=pY;
    highlighter->setPos(pX*64, pY*64);
}
