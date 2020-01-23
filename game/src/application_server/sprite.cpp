#include "sprite.h"
#include <QDebug>

Sprite::Sprite(QImage * pImage, int pCount, int size):
    count{pCount}
{
    int rowWidth = pImage->width() / size;
    int x{0},y{0};
    for(int i = 0; i<count; i++){
        images.push_back(pImage->copy(x,y,size,size));
        if(x>pImage->width()-size){
            x=0;
            y+=size;
        }
        x+=size;
    }
    qDebug() << "Read " << images.length();
}

/**
 * @brief Sprite::getImage Liefert das aktuelle Bild des Sprites zurück.
 * @return Das aktuelle Bild.
 */
QImage Sprite::getImage()
{
    return images.at(index);
}

/**
 * @brief Sprite::step Führt einen Animationsschritt durch.
 */
void Sprite::step()
{
    index++;
    if(index>=count){
        index=0;
    }
}
