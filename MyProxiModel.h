#pragma once

#include <QObject>
#include <QSortFilterProxyModel>

#include "Model.h"

class MyProxiModel : public QSortFilterProxyModel
{
public:
    MyProxiModel(QObject *parent = nullptr);

    virtual QVariant data(const QModelIndex &index, int role) const override;
    virtual bool setData(const QModelIndex& index, const QVariant& value, int role) override;
    virtual Qt::ItemFlags flags(const QModelIndex& index) const override;
    virtual int rowCount(const QModelIndex& /*parent*/) const override;

};

