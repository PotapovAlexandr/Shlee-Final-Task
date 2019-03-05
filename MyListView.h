#pragma once
#include <QObject>
#include <QtWidgets>

#include "Model.h"

class MyListView : public QListView
{
public:
    MyListView(QWidget* parent = nullptr);
    ~MyListView(){}

    QModelIndexList SelectedIndexesList() const;
};






