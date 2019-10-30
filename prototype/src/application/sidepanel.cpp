#include "sidepanel.h"
#include <QGroupBox>
#include <QVBoxLayout>
#include <QPalette>

/**
 * @brief SidePanel::SidePanel Erzeugt ein neues Side-Panel (Menü)
 * @param pParent Das Parent-Element
 */
SidePanel::SidePanel()
{
    setFixedWidth(80);


    layout = new QGridLayout(this);
    setLayout(layout);

    moneyLabel = new QLabel();
    layout->addWidget(moneyLabel);

    timeLabel = new QLabel();
    layout->addWidget(timeLabel);

    positionLabel = new QLabel();
    layout->addWidget(positionLabel);
}

/**
 * @brief SidePanel::hookDataModel Verknüpft ein Datenmodell mit der Anzeige. Dadurch können dann Textfelder etc. aktualisiert werden.
 * @param pModel Ein Datenmodell.
 */
void SidePanel::hookDataModel(DataModel *pModel){
    pModel->setGuiBalanceLabel(moneyLabel);
    pModel->setGuiTimeLabel(timeLabel);
    pModel->setGuiPositionLabel(positionLabel);
}
