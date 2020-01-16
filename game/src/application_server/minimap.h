#ifndef MINIMAP_H
#define MINIMAP_H

#include <QWidget>
#include "maprenderer.h"


class Minimap: public QWidget
{
    Q_OBJECT
public:
    Minimap(int,int, MapRenderer *, DataModel *);
    void paintEvent(QPaintEvent *event) override;

private:
    void renderMap();
    int width,height;
    MapRenderer * scene;
    DataModel * dataModel;
    QImage location,compass,location_white,mapOverlay,map;

public slots:
    void viewChange();
};

#endif // MINIMAP_H
