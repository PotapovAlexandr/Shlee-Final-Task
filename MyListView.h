#pragma once
#include <QObject>
#include <QtWidgets>
#include <QApplication>

#include "Model.h"


class MyListItemDelegate: public QStyledItemDelegate
{
public:
    MyListItemDelegate(QWidget* parent = nullptr):QStyledItemDelegate(parent)
    {}

    QSize sizeHint(const QStyleOptionViewItem& /*option*/, const QModelIndex& /*index*/) const override
    {
        return QSize(130, 130);
    }

    virtual void paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const override
    {
        if (!index.isValid())
        {
            return;
        }


        QRect rectForHeader = QRect(option.rect.x(), option.rect.y() , option.rect.width(), 20);
        QRect rectForPict = QRect( option.rect.x() + 20, option.rect.y() + 20 , 60, 40);
        QRect rectForLinc = QRect(option.rect.x(), option.rect.y() + 60 , option.rect.width(), 20);
        QRect rectForDate = QRect(option.rect.x(), option.rect.y() + 80 , option.rect.width(), 20);

        QPixmap img = index.data(PreviewRole).value<QPixmap>();

        painter->drawText(rectForHeader, index.data(HeaderRole).toString());
        painter->drawPixmap(rectForPict, img);
        painter->drawText(rectForLinc, "Linc");
        painter->drawText(rectForDate, "Date:" + index.data(CreationDateRole).toString());
        painter->drawRoundedRect(option.rect, 5, 5);
    }

    QWidget *createEditor(QWidget *parent,
                          const QStyleOptionViewItem &option,
                          const QModelIndex &index) const override
    {
        QLineEdit* editor = new QLineEdit(parent);
        editor->setAutoFillBackground(true);
        return editor;
    }

    void setEditorData(QWidget *editor, const QModelIndex &index) const override
    {
        QLineEdit* lineEditor = static_cast<QLineEdit*>(editor);
        lineEditor->setText(index.data(HeaderRole).toString());
    }

    void updateEditorGeometry(QWidget *editor,
                              const QStyleOptionViewItem &option,
                              const QModelIndex &index) const override
    {
        editor->setGeometry(QRect(option.rect.x(), option.rect.y() , option.rect.width(), 20));
    }
};


class MyListView : public QListView
{
public:
    MyListView(QWidget* parent = nullptr): QListView(parent)
    {
        setResizeMode(QListView::Fixed);
        setGridSize(QSize(150, 150));
        setWrapping( true );
        setFlow(QListView::LeftToRight);
        //setSelectionMode(QAbstractItemView::ExtendedSelection);
        //setSelectionBehavior(QAbstractItemView::SelectItems);


        MyListItemDelegate* delegate = new MyListItemDelegate(this);
        setItemDelegate(delegate);
    }
    ~MyListView(){}


};

