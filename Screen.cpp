#include <QtWidgets>
#include <QMediaPlayer>
//#include <QVideoWidget>

#include "Screen.h"

Screen::Screen(QWidget *parent): QLabel(parent)
{
    setScaledContents(true);
}

void Screen::LoadFile(const QString &filePath)
{
    QString fileSuffix = QFileInfo(filePath).suffix();
    if (fileSuffix == "jpeg" || fileSuffix == "jpg")
    {
        setPixmap(QPixmap(filePath));
    }
    else if (fileSuffix == "avi")
    {
        QMediaPlayer player;
        player.setMedia(QUrl::fromLocalFile(filePath));
        player.play();
//        QVideoWidget videoWidget;
//        player.setVideoOutput(videoWidget);
    }
}

void Screen::keyPressEvent(QKeyEvent* /*event*/)
{
    close();
}
