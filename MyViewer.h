#pragma once
#include <QtWidgets>
#include <QListView>


class MyViewer: public QListView
{
    MyViewer(QWidget* parent = nullptr): QListView(parent){}
};
