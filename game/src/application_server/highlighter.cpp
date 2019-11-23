#include "highlighter.h"

#include <QPen>

Highlighter::Highlighter()
{
    setRect(0,0,64,64);
    outline = new QPen();
    outline->setColor(QColor(Qt::white));
    outline->setWidth(2);
    setPen(*outline);
    setZValue(2);
}

void Highlighter::setColor(QColor pColor)
{
    outline->setColor(pColor);
    setPen(*outline);
}
