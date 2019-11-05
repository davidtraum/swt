#ifndef TOOLTIPMENU_H
#define TOOLTIPMENU_H
#include <QWidget>
#include <QLabel>
#include <QGroupBox>
#include <QGridLayout>


class ToolTipMenu: public QWidget
{
public:
    ToolTipMenu();

    void hide();
    void showAt(int x, int y);
    void setText(QString pText);

private:
    QLabel * textlabel;
};

#endif // TOOLTIPMENU_H
