#ifndef SIDEPANEL_H
#define SIDEPANEL_H

#include <QWidget>
#include <QGridLayout>
#include <QLabel>

#include "datamodel.h"
#include "minimap.h"


class SidePanel: public QWidget
{
public:
    SidePanel(Minimap *);
    void hookDataModel(DataModel * pModel);
private:
    QGridLayout * layout;
    QLabel * moneyLabel;
    QLabel * timeLabel;
    QLabel * positionLabel;
    Minimap * miniMap;
};

#endif // SIDEPANEL_H
