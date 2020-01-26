#ifndef INFOWIDGET_H
#define INFOWIDGET_H

#include <QLabel>
#include <QWidget>

class InfoWidget: public QWidget
{
public:
    InfoWidget();
    QLabel * headerLabel;
    QLabel * headerGut;
    QLabel * headerLager;
    QLabel * headerPreis;

    void setContentGut(QString);
    void setContentLager(QString);
    void setContentPreis(QString);

    QString getContentGut();
    QString getContentLager();
    QString getContentPreis();


private:
    QLabel * contentGut;
    QLabel * contentLager;
    QLabel * contentPreis;



};

#endif // INFOWIDGET_H
