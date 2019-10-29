#ifndef SIDEPANEL_H
#define SIDEPANEL_H

#include <QWidget>
#include <QGridLayout>
#include <QLabel>

#include "datamodel.h"


class SidePanel: public QWidget
{
public:
    SidePanel();
    void hookDataModel(DataModel * pModel);
private:
    QGridLayout * layout;
    QLabel * moneyLabel;
    QLabel * timeLabel;
};

#endif // SIDEPANEL_H
