#include <QtWidgets>
#include <QVideoWidget>

#include "Screen.h"

Screen::Screen(QWidget *parent):
    QLabel(parent)
  , m_player( new QMediaPlayer(this))
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
        m_player->setAudioRole(QAudio::VideoRole);
        m_player->setMedia(QUrl::fromLocalFile(filePath));

        QVideoWidget* videoWidget = new QVideoWidget(this);
        m_player->setVideoOutput(videoWidget);

        QHBoxLayout* layout = new QHBoxLayout(this);
        layout->addWidget(videoWidget);

        setLayout(layout);
        m_player->play();
    }
}

void Screen::keyPressEvent(QKeyEvent* /*event*/)
{
    if(m_player->isAvailable())
    {
        m_player->stop();
    }
    close();
}
