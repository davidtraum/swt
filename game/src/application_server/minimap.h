#ifndef MINIMAP_H
#define MINIMAP_H

#include <QWidget>
#include "maprenderer.h"
#include "point.h"


class Minimap: public QWidget
{
    Q_OBJECT
public:
    Minimap(int,int, MapRenderer *, DataModel *);
    void paintEvent(QPaintEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;

private:
    void renderMap();
    int width,height;
    MapRenderer * scene;
    Point hoverCoords{0,0};
    int renderCoordinates{0};
    DataModel * dataModel;
    QImage location,compass,location_white,mapOverlay,map;

public slots:
    void viewChange();
};

#endif // MINIMAP_H
