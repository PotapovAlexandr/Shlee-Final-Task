#include "MyListView.h"
#include "MyListItemDelegate.h"

MyListView::MyListView(QWidget* parent): QListView(parent)
{
    setResizeMode(QListView::Fixed);
    setGridSize(QSize(150, 150));
    setWrapping(true);
    setFlow(QListView::LeftToRight);

    MyListItemDelegate* delegate = new MyListItemDelegate(this);
    setItemDelegate(delegate);
}

QModelIndexList MyListView::SelectedIndexesList() const
{
    return QListView::selectedIndexes();
}



