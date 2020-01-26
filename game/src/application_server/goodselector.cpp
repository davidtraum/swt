#include "goodselector.h"

#include <QPushButton>
#include <QGridLayout>
#include <QCursor>
#include <QDebug>

GoodSelector::GoodSelector()
{
    QString list[] = {"CORN", "COAL", "MAIL", "PASSENGERS", "FOOD", "LIVESTOCK", "GOODS", "PAPER", "STEEL", "PETROLEUM", "WOOD"};
    QString names[] = {"Weizen", "Kohle", "Post", "Passagiere", "Essen", "Tiere", "Pakete", "Papier", "Stahl", "Petroleum", "Holz"};

    QGridLayout * layout = new QGridLayout();
    layout->setAlignment(Qt::AlignTop);

    int row{0},col{0},index{0};
    for(QString entry : list){
        QPushButton * btn = new QPushButton();
        btn->setIcon(QIcon(":/icons/icon_" + entry));
        btn->setToolTip(names[index]);
        btn->setCursor(QCursor(Qt::PointingHandCursor));
        connect(btn, &QPushButton::pressed, this, [=] () {
            emit addWagonClicked(new QString(entry));
        });
        layout->addWidget(btn, row,col);
        col++;
        if(col>=3){
            row++;
            col = 0;
        }
        index++;
    }

    this->setLayout(layout);
}
