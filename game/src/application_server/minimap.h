#ifndef MINIMAP_H
#define MINIMAP_H

#include <QWidget>
#include "scene.h"
#include "view.h"


class Minimap: public QWidget
{
    Q_OBJECT
public:
    Minimap(int,int, Scene *, View *, DataModel *);
    void paintEvent(QPaintEvent *event) override;

private:
    int width,height;
    Scene * scene;
    DataModel * dataModel;
    View * view;
    QImage location,compass,location_white,mapOverlay;

public slots:
    void viewChange();
};

#endif // MINIMAP_H
