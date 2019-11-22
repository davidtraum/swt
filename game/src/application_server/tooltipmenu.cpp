#include "tooltipmenu.h"

/**
 * @brief ToolTipMenu::ToolTipMenu Erzeugt ein Tool-Tip Menü das absolut positioniert werden kann.
 */
ToolTipMenu::ToolTipMenu()
{
    hide();
    textlabel = new QLabel();
    textlabel->setStyleSheet("border: 2px solid black; background-color: rgba(255,255,255,180); border-top-right-radius: 20px; border-bottom-right-radius: 20px; border-bottom-left-radius: 20px; color: black;");
    QGridLayout * layout = new QGridLayout(this);
    QWidget::setLayout(layout);
    layout->addWidget(textlabel);

}

/**
 * @brief ToolTipMenu::hide Blendet das Menü aus.
 */
void ToolTipMenu::hide()
{
    QWidget::setFixedSize(0, 0);
}

/**
 * @brief ToolTipMenu::showAt Blendet das Menü an einer bestimmten Stelle (relativ zum Parent) ein.
 * @param x Die X-Koordinate.
 * @param y Die Y-Koordinate.
 */
void ToolTipMenu::showAt(int x, int y)
{
    QWidget::move(x,y);
    QWidget::setVisible(true);
    QWidget::setFixedSize(100, 100);


}

/**
 * @brief ToolTipMenu::setText Setzt den Text. (HTML-Fähig)
 * @param pText Der Text als QString.
 */
void ToolTipMenu::setText(QString pText)
{
    textlabel->setText(pText);
}
