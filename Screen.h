#pragma once

#include <QObject>
#include <QLabel>

class Screen: public QLabel
{
public:
    Screen(QWidget* parent = nullptr);

    void LoadFile(const QString& filePath);

    virtual void keyPressEvent(QKeyEvent *event) override;

};
