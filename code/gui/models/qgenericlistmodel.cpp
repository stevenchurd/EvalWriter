// (C) Copyright Steven Hurd 2013

#include "qgenericlistmodel.h"

QGenericListModel::QGenericListModel(QObject* parent) :
    QAbstractListModel(parent)
{
}


int QGenericListModel::rowCount(const QModelIndex &/*parent*/) const
{
    return getNumItems();
}


QVariant QGenericListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (index.row() >= getNumItems())
        return QVariant();

    switch(role)
    {
        case Qt::DisplayRole:
        case StringRole:
            return QVariant::fromValue(
                        QString::fromStdString(getItemString(index.row())));
            break;

        default:
            return QVariant();
            break;
    }

}


QHash<int,QByteArray> QGenericListModel::roleNames() const
{
    static QHash<int, QByteArray> roleNames;

    if (roleNames.isEmpty())
    {
        roleNames[StringRole] = "displayString";
    }

    return roleNames;
}

