#include "infowidget.h"

#include <QVBoxLayout>
#include <QDebug>
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
    contentGut->setText("Getreide \nKohle \nPassagiere \nMail \nVieh \nPakete \nPapier \nStahl \nPetroleum \nHolz \nNahrung");
    hLayoutContent->addWidget(contentGut);

    contentLager = new QLabel();
    contentLager->setText("NAN \nNAN \nNAN \nNAN \nNAN \nNAN \nNAN \nNAN \nNAN \nNAN \nNAN");
    hLayoutContent->addWidget(contentLager);

    contentPreis = new QLabel();
    contentPreis->setText("NAN \nNAN \nNAN \nNAN \nNAN \nNAN \nNAN \nNAN \nNAN \nNAN \nNAN");
    hLayoutContent->addWidget(contentPreis);

    hLayoutContent->setAlignment(Qt::AlignTop);
    vLayout->setAlignment(Qt::AlignTop);
    vLayout->addLayout(hLayoutHeader);
    vLayout->addLayout(hLayoutContent);


    setStyleSheet("background-color:rgb(150,150,255)");

    QWidget::setLayout(vLayout);

}

void InfoWidget::setContentGut(QString str) {
    qDebug() << "in setContentGut" << str;
    contentGut->setText(str);
    qDebug() << "danach";
}
void InfoWidget::setContentLager(QString str) {
    qDebug() << "in setContentLager" << str;
    contentLager->setText(str);
    qDebug() << "danach";
}
void InfoWidget::setContentPreis(QString str) {
    qDebug() << "in setContentPreis" << str;
    contentPreis->setText(str);
    qDebug() << "danach";
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

void InfoWidget::sendInfoRequest(int x, int y){
    emit sendInfoSignal(x,y);
}
