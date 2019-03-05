#pragma once

#include <QObject>
#include <QSortFilterProxyModel>

#include "Model.h"

class MyProxiModel : public QSortFilterProxyModel
{
public:
    MyProxiModel(QObject *parent = nullptr);

public slots:
    void ChangeFilter(const QString& newFilter);

protected:
    virtual bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const override;
    virtual bool lessThan(const QModelIndex& sourceLeft, const QModelIndex& sourceRight) const override;

private:
    QString m_filter;
};

