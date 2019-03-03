#include "MyProxiModel.h"

MyProxiModel::MyProxiModel(QObject *parent): QSortFilterProxyModel(parent)
{
}

QVariant MyProxiModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
    {
        return QVariant();
    }
    return sourceModel()->data(index, role);
}

bool MyProxiModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid())
    {
        return false;
    }
    if (role == Qt::EditRole)
    {
        sourceModel()->setData(index, value, role);
    }
    return true;
}

Qt::ItemFlags MyProxiModel::flags(const QModelIndex &index) const
{
    if(!index.isValid())
    {
        return Qt::NoItemFlags;
    }
    return  sourceModel()->flags(index);
}

int MyProxiModel::rowCount(const QModelIndex &) const
{
    return  sourceModel()->rowCount();
}
