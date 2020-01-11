#include "routeinterface.h"

#include <QDebug>

#include <QHBoxLayout>

/**
 * @brief RouteInterface::RouteInterface Erzeugt das Routeninterface.
 */
RouteInterface::RouteInterface()
{
    QDockWidget::setFeatures(nullptr);
    QDockWidget::setVisible(false);

    QHBoxLayout * layout = new QHBoxLayout();

    trainRenderer = new TrainRenderer();
    layout->addWidget(trainRenderer);

    QDockWidget::setLayout(layout);
}

/**
 * @brief RouteInterface::toggle Wechselt die Sichtbarkeit des Widgets.
 */
void RouteInterface::toggle() {
    QDockWidget::setVisible(!QDockWidget::isVisible());
    qDebug() << this->isVisible();
}
