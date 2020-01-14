#ifndef TRAINRENDERER_H
#define TRAINRENDERER_H

#include <QWidget>
#include "graphicsmanager.h"


class TrainRenderer: public QWidget
{
    Q_OBJECT
public:
    TrainRenderer(GraphicsManager *);
    void paintEvent(QPaintEvent *event) override;
    void addWagon(std::string name);
    void deleteAllWagons();
    std::map<std::string, int> wagons;

private:
    QImage train,background,sky,wagon;
    GraphicsManager * graphicsManager;

private slots:
    void mouseReleaseEvent(QMouseEvent *event) override;
signals:
    void triggerRemoveWagon();
};

#endif // TRAINRENDERER_H
