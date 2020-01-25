#include "infowidget.h"
#include <QVBoxLayout>
/**
 * @brief InfoWidget::InfoWidget Erzeugt ein Info Widget
 */
InfoWidget::InfoWidget()
{
    QVBoxLayout * mainLayout = new QVBoxLayout();

    setFixedSize(300,300);

    hide();


    QWidget::setLayout(mainLayout);

}
