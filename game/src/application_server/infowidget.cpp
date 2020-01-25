#include "infowidget.h"
#include <QVBoxLayout>
/**
 * @brief InfoWidget::InfoWidget Erzeugt ein Info Widget
 */
InfoWidget::InfoWidget()
{
    QVBoxLayout * mainLayout = new QVBoxLayout();
    time = new QLCDNumber();
    time->display(123);
    money = new QLCDNumber();
    money->display(3456);
    mainLayout->addWidget(time);
    mainLayout->addWidget(money);

    QWidget::setLayout(mainLayout);

}
