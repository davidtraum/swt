#include "videowidget.h"

#include <QGroupBox>
#include <QHBoxLayout>
#include <QDebug>
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QMediaPlaylist>

Videowidget::Videowidget() {

    QDockWidget::setFeatures(nullptr);
    QDockWidget::setVisible(false);

    QGroupBox * mainWidget = new QGroupBox(" Routen verwalten");

    QVBoxLayout * layout = new QVBoxLayout(mainWidget);

    layout->setAlignment(Qt::AlignCenter);

    mainWidget->setLayout(layout);

    QMediaPlayer * player = new QMediaPlayer;

    QMediaPlaylist * playlist = new QMediaPlaylist(player);
    playlist->addMedia(QUrl("qrc:/video/building_bridge.mp4"));

    QVideoWidget * videoWidget = new QVideoWidget;
    player->setVideoOutput(videoWidget);

    videoWidget->show();

    layout->addWidget(videoWidget);

    layout->setAlignment(Qt::AlignBottom);

    QDockWidget::setWidget(mainWidget);
    mainWidget->setStyleSheet("background-color:rgb(150,150,255)");
}

void Videowidget::toggle() {
    if (this->isVisible()) {
        QDockWidget::setVisible(false);
    }
    else {
        QDockWidget::setVisible(true);

        qDebug() << "Video startet";
        player->play();
    }
}
