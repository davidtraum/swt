#ifndef MINIMAP_H
#define MINIMAP_H

#include <QWidget>
#include "scene.h"


class Minimap: public QWidget
{
    Q_OBJECT
public:
    Minimap(int,int, Scene *, DataModel *);
    void paintEvent(QPaintEvent *event) override;

private:
    int width,height;
    Scene * scene;
    DataModel * dataModel;

public slots:
    void viewChange();
};

#endif // MINIMAP_H
