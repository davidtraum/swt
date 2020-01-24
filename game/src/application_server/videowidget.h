#ifndef VIDEOWIDGET_H
#define VIDEOWIDGET_H

#include <QWidget>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QDockWidget>
#include <QMediaPlayer>

#include "graphicsmanager.h"

class Videowidget : public QDockWidget
{
    Q_OBJECT
public:
    explicit Videowidget();

private:
    QMediaPlayer * player;
    QVideoWidget * videoWidget;

signals:

public slots:
    void toggle();

};

#endif // VIDEOWIDGET_H
