#include "infowidget.h"
#include <QVBoxLayout>
/**
 * @brief InfoWidget::InfoWidget Erzeugt ein Info Widget
 */
InfoWidget::InfoWidget()
{
    QVBoxLayout * vLayout = new QVBoxLayout();
    QHBoxLayout * hLayoutHeader = new QHBoxLayout();
    QHBoxLayout * hLayoutContent = new QHBoxLayout();

    setFixedSize(300,300);

    hide();

    headerLabel = new QLabel();
    headerLabel->setText("Informations-Interface");
    vLayout->addWidget(headerLabel);

    headerGut = new QLabel();
    headerGut->setText("Güter:");
    hLayoutHeader->addWidget(headerGut);

    headerLager = new QLabel();
    headerLager->setText("Lager:");
    hLayoutHeader->addWidget(headerLager);

    headerPreis = new QLabel();
    headerPreis->setText("Preise:");
    hLayoutHeader->addWidget(headerPreis);

    contentGut = new QLabel();
    contentGut->setText("Getreide \nKohle \nPassagiere \nMail \nVieh \nPakete \nHolz \nStahl \nNahrung \nPetroleum \nPapier");
    hLayoutContent->addWidget(contentGut);

    contentGut = new QLabel();
    contentGut->setText("NAN \nNAN \nNAN \nNAN \nNAN \nNAN \nNAN \nNAN \nNAN \nNAN \nNAN");
    hLayoutContent->addWidget(contentGut);

    contentGut = new QLabel();
    contentGut->setText("NAN \nNAN \nNAN \nNAN \nNAN \nNAN \nNAN \nNAN \nNAN \nNAN \nNAN");
    hLayoutContent->addWidget(contentGut);

    vLayout->setAlignment(Qt::AlignTop);
    vLayout->addLayout(hLayoutHeader);
    vLayout->addLayout(hLayoutContent);

    setStyleSheet("background-color:rgb(150,150,255)");

    QWidget::setLayout(vLayout);

}

void InfoWidget::setContentGut(QString str) {
    contentGut->setText(str);
}
void InfoWidget::setContentLager(QString str) {
    contentLager->setText(str);
}
void InfoWidget::setContentPreis(QString str) {
    contentPreis->setText(str);
}

QString InfoWidget::getContentGut() {
    return contentGut->text();
}
QString InfoWidget::getContentLager() {
    return contentLager->text();
}
QString InfoWidget::getContentPreis() {
    return contentPreis->text();
}
