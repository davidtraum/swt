#include "tooltipmenu.h"

ToolTipMenu::ToolTipMenu()
{
    QWidget::setStyleSheet("background-color: rgba(255,255,255,200)");
    hide();
    textlabel = new QLabel();
    QGridLayout * layout = new QGridLayout(this);
    QWidget::setLayout(layout);
    layout->addWidget(textlabel);

}

void ToolTipMenu::hide()
{
    QWidget::setFixedSize(0, 0);
}

void ToolTipMenu::showAt(int x, int y)
{
    QWidget::move(x,y);
    QWidget::setVisible(true);
    QWidget::setFixedSize(100, 100);


}

void ToolTipMenu::setText(QString pText)
{
    textlabel->setText(pText);
}
