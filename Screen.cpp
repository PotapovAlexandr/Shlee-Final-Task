#include <QtWidgets>

#include "Screen.h"

Screen::Screen(QWidget *parent): QLabel(parent)
{
    setScaledContents(true);
    //setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );
}

void Screen::keyPressEvent(QKeyEvent* /*event*/)
{
    close();
}
