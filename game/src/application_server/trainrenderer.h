#ifndef TRAINRENDERER_H
#define TRAINRENDERER_H

#include <QWidget>
#include "graphicsmanager.h"


class TrainRenderer: public QWidget
{
public:
    TrainRenderer(GraphicsManager *);
    void paintEvent(QPaintEvent *event) override;
    void addWagon(std::string name);
    void deleteAllWagons();

private:
    QImage train,background,sky,wagon;
    GraphicsManager * graphicsManager;
    std::map<std::string, int> wagons;

private slots:
    void mouseReleaseEvent(QMouseEvent *event) override;
};

#endif // TRAINRENDERER_H
