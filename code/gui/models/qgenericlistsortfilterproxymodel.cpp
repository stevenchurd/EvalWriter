#include "qgenericlistsortfilterproxymodel.h"
#include "qgenericlistmodel.h"

QGenericListSortFilterProxyModel::QGenericListSortFilterProxyModel(QObject *parent) :
    QSortFilterProxyModel(parent)
{
    setFilterCaseSensitivity(Qt::CaseInsensitive);
}


QList<int> QGenericListSortFilterProxyModel::getSubModelOperations() const
{
    QGenericListModel* genericListModel = dynamic_cast<QGenericListModel*>(sourceModel());
    return genericListModel->getSubModelOperations();
}


QObject* QGenericListSortFilterProxyModel::getNextPageFromIndex(int row) const
{
    QGenericListModel* genericListModel = dynamic_cast<QGenericListModel*>(sourceModel());
    QModelIndex newIndex = mapToSource(index(row, 0));
    return genericListModel->getNextPageFromIndex(newIndex.row());
}


QStringList QGenericListSortFilterProxyModel::getOptionListForOperation(int operation) const
{
    QGenericListModel* genericListModel = dynamic_cast<QGenericListModel*>(sourceModel());
    return genericListModel->getOptionListForOperation(operation);
}


QString QGenericListSortFilterProxyModel::getOperationExplanationText(int operation, int row) const
{
    QGenericListModel* genericListModel = dynamic_cast<QGenericListModel*>(sourceModel());
    QModelIndex newIndex = mapToSource(index(row, 0));
    return genericListModel->getOperationExplanationText(operation, newIndex.row());
}


void QGenericListSortFilterProxyModel::addItem(QString newName) const
{
    QGenericListModel* genericListModel = dynamic_cast<QGenericListModel*>(sourceModel());
    genericListModel->addItem(newName);
}


void QGenericListSortFilterProxyModel::removeItem(int row) const
{
    QGenericListModel* genericListModel = dynamic_cast<QGenericListModel*>(sourceModel());
    QModelIndex newIndex = mapToSource(index(row, 0));
    genericListModel->removeItem(newIndex.row());
}


void QGenericListSortFilterProxyModel::renameItem(QString newName, int row) const
{
    QGenericListModel* genericListModel = dynamic_cast<QGenericListModel*>(sourceModel());
    QModelIndex newIndex = mapToSource(index(row, 0));
    genericListModel->renameItem(newName, newIndex.row());
}


void QGenericListSortFilterProxyModel::optionListSelection(int operation, int row) const
{
    QGenericListModel* genericListModel = dynamic_cast<QGenericListModel*>(sourceModel());
    QModelIndex newIndex = mapToSource(index(row, 0));
    genericListModel->optionListSelection(operation, newIndex.row());
}
