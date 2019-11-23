#ifndef HIGHLIGHTER_H
#define HIGHLIGHTER_H

#include <QGraphicsRectItem>

class Highlighter: public QGraphicsRectItem
{
public:
    Highlighter();
    void setColor(QColor pColor);
private:
    QPen * outline;
};

#endif // HIGHLIGHTER_H
