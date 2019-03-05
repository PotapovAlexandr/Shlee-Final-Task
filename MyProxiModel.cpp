#include "MyProxiModel.h"

MyProxiModel::MyProxiModel(QObject *parent): QSortFilterProxyModel(parent)
{
}

void MyProxiModel::ChangeFilter(const QString& newFilter)
{
    m_filter= newFilter;
    invalidate();
}

bool MyProxiModel::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const
{
    if (m_filter.isEmpty())
    {
        return true;
    }
    QModelIndex index = sourceModel()->index(sourceRow, 0, sourceParent);
    return index.data(HeaderRole).toString().contains(m_filter, Qt::CaseInsensitive);
}

bool MyProxiModel::lessThan(const QModelIndex& sourceLeft, const QModelIndex& sourceRight) const
{
    if (sortRole() == HeaderRole)
    {
        return sourceLeft.data(HeaderRole).toString() < sourceRight.data(HeaderRole).toString();
    }
    else
    {
        return sourceLeft.data(CreationDateRole).toDate() < sourceRight.data(CreationDateRole).toDate();
    }
}
