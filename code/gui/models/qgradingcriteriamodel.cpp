// (C) Copyright Steven Hurd 2013

#include "qgradingcriteriamodel.h"
#include "model/criteriaitem.h"
#include "model/gradingcriteria.h"

QGradingCriteriaModel::QGradingCriteriaModel(
        QVector<boost::shared_ptr<GradingCriteria> > &gradingCriteria, QObject *parent) :
    QAbstractListModel(parent), m_gradingCriteria(gradingCriteria)
{
    foreach(boost::shared_ptr<GradingCriteria> gc, m_gradingCriteria)
    {
        m_criteriaItemListModels.push_back(new QCriteriaItemListModel(gc, this));
        m_rowExpanded.push_back(false);
    }
}


Qt::ItemFlags QGradingCriteriaModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return 0;

    return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}


int QGradingCriteriaModel::rowCount(const QModelIndex &/*parent*/) const
{
    return m_gradingCriteria.size();
}


QVariant QGradingCriteriaModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (index.row() > m_gradingCriteria.size() || index.row() < 0)
        return QVariant();

    switch(role)
    {
        case Qt::DisplayRole:
        case StringRole:
            return QString::fromStdString(m_gradingCriteria[index.row()]->getCriteriaName());
            break;

        case NumCriteriaItemsRole:
            return QVariant::fromValue(m_gradingCriteria[index.row()]->getNumCriteriaItems());
            break;

        case IsExpandedRole:
            return QVariant::fromValue(m_rowExpanded[index.row()]);
            break;

        default:
            return QVariant();
            break;
    }
}


QHash<int,QByteArray> QGradingCriteriaModel::roleNames() const
{
    static QHash<int, QByteArray> roleNames;

    if (roleNames.isEmpty())
    {
        roleNames[StringRole] = "gradingCriteriaString";
        roleNames[NumCriteriaItemsRole] = "numCriteriaItems";
        roleNames[IsExpandedRole] = "isExpanded";
    }

    return roleNames;
}


void QGradingCriteriaModel::expandRow(int row)
{
    QModelIndex qmi = index(row);
    m_rowExpanded[row] = true;
    dataChanged(qmi, qmi);
}


void QGradingCriteriaModel::collapseRow(int row)
{
    QModelIndex qmi = index(row);
    m_rowExpanded[row] = false;
    dataChanged(qmi, qmi);
}


void QGradingCriteriaModel::removeGradingCriteria(int row)
{
    beginRemoveRows(QModelIndex(), row, row);
    m_gradingCriteria.remove(row);
    m_criteriaItemListModels.remove(row);
    m_rowExpanded.remove(row);
    endRemoveRows();
}

void QGradingCriteriaModel::removeCriteriaItem(int row, int subrow)
{
    // remove it from the contained model
    m_criteriaItemListModels[row]->removeCriteriaItem(subrow);

    if(m_gradingCriteria[row]->getNumCriteriaItems() <= 0)
    {
        m_rowExpanded[row] = false;
    }

    QModelIndex qmi = index(row);
    emit dataChanged(qmi, qmi);
}

