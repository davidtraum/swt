#include "player.h"

#include <QPen>
Player::Player(int pId)
{
    highlighter = new QGraphicsRectItem();
    highlighter->setRect(0,0,64,64);
    QPen * outline = new QPen();
    outline->setColor(QColor(Qt::green));
    outline->setWidth(2);
    highlighter->setPen(*outline);
    highlighter->setZValue(2);

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
