#ifndef SPRITE_H
#define SPRITE_H

#include <QImage>
#include <QList>

class Sprite
{
public:
    Sprite(QImage *, int,int);
    QImage getImage();
    void step();

private:
    QList<QImage> images;
    int index{0};
    int count;

};

#endif // SPRITE_H
