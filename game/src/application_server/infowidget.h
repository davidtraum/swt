#ifndef INFOWIDGET_H
#define INFOWIDGET_H

#include <QLabel>
#include <QWidget>

class InfoWidget: public QWidget
{
    Q_OBJECT
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

    void sendInfoRequest(int,int);


private:
    QLabel * contentGut;
    QLabel * contentLager;
    QLabel * contentPreis;

signals:

    void sendInfoSignal(int,int);


};

#endif // INFOWIDGET_H
