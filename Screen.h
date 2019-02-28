#pragma once

#include <QObject>
#include <QLabel>

class Screen : public QLabel
{
public:
    Screen(QWidget* parent = nullptr);

    virtual void keyPressEvent(QKeyEvent *event) override;
};
