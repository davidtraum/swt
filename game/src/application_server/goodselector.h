#ifndef GOODSELECTOR_H
#define GOODSELECTOR_H

#include <QWidget>

class GoodSelector: public QWidget
{
    Q_OBJECT
public:
    GoodSelector();

signals:
    void addWagonClicked(QString *);
};

#endif // GOODSELECTOR_H
