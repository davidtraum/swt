#include "sidepanel.h"
#include <QGroupBox>
#include <QVBoxLayout>

/**
 * @brief SidePanel::SidePanel Erzeugt ein neues Side-Panel (Menü)
 * @param pParent Das Parent-Element
 */
SidePanel::SidePanel()
{
    layout = new QGridLayout(this);
    setLayout(layout);

    moneyLabel = new QLabel();
    layout->addWidget(moneyLabel);

    timeLabel = new QLabel();
    layout->addWidget(timeLabel);

    QGroupBox * groupBox = new QGroupBox("Spiel", moneyLabel);
    QVBoxLayout * boxLayout = new QVBoxLayout(groupBox);
    layout->addWidget(groupBox,0,0);
}

/**
 * @brief SidePanel::hookDataModel Verknüpft ein Datenmodell mit der Anzeige. Dadurch können dann Textfelder etc. aktualisiert werden.
 * @param pModel Ein Datenmodell.
 */
void SidePanel::hookDataModel(DataModel *pModel){
    pModel->setGuiBalanceLabel(moneyLabel);
    pModel->setGuiTimeLabel(timeLabel);
}
