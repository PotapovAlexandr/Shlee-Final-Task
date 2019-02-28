#pragma once
#include <QObject>
#include <QtWidgets>
#include <QApplication>

#include "Model.h"
#include "Screen.h"


class MyListItemDelegate: public QStyledItemDelegate
{
public:
    MyListItemDelegate(QWidget* parent = nullptr):QStyledItemDelegate(parent)
    {}

    virtual QSize sizeHint(const QStyleOptionViewItem& /*option*/, const QModelIndex& /*index*/) const override;
    virtual void paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const override;
    virtual bool editorEvent(QEvent* event,
                             QAbstractItemModel* model,
                             const QStyleOptionViewItem& option,
                             const QModelIndex& index) override;
    virtual QWidget *createEditor(QWidget *parent,
                          const QStyleOptionViewItem &option,
                          const QModelIndex &index) const override;

    virtual void setEditorData(QWidget *editor, const QModelIndex &index) const override;

    virtual void updateEditorGeometry(QWidget *editor,
                              const QStyleOptionViewItem &option,
                              const QModelIndex &index) const override;
};


class MyListView : public QListView
{
public:
    MyListView(QWidget* parent = nullptr);

    ~MyListView(){}


};

