#include "qmainnavigationmodel.h"

QMainNavigationModel::QMainNavigationModel(QObject *parent) :
    QAbstractListModel(parent)
{
}


QObject* QMainNavigationModel::getSubModel(int index) const
{
    return static_cast<QObject*>(std::get<1>(m_submodels[index]).get());
}


void QMainNavigationModel::addSubModel(std::string displayString, std::shared_ptr<QGenericListModel> listModel)
{
    m_submodels.push_back(std::make_tuple(displayString, listModel));
}


int QMainNavigationModel::rowCount(const QModelIndex &/*parent*/) const
{
    return m_submodels.size();
}


QVariant QMainNavigationModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (index.row() >= static_cast<int>(m_submodels.size()))
        return QVariant();

    switch(role)
    {
        case Qt::DisplayRole:
        case StringRole:
            return QVariant::fromValue(
                        QString::fromStdString(std::get<0>(m_submodels[index.row()])));
            break;

        default:
            return QVariant();
            break;
    }

}


QHash<int,QByteArray> QMainNavigationModel::roleNames() const
{
    static QHash<int, QByteArray> roleNames;

    if (roleNames.isEmpty())
    {
        roleNames[StringRole] = "submodelName";
    }

    return roleNames;
}

