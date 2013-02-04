#include "qcriteriaitemlistmodel.h"

QCriteriaItemListModel::QCriteriaItemListModel(boost::shared_ptr<GradingCriteria> gradingCriteria, int parentIndex,
                   QObject* parent) :
    QAbstractListModel(parent), m_parentIndex(parentIndex), m_gradingCriteria(gradingCriteria)
{
}

int QCriteriaItemListModel::rowCount(const QModelIndex &/*parent*/) const
{
    return m_gradingCriteria->getNumCriteriaItems();
}


QVariant QCriteriaItemListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (index.row() >= m_gradingCriteria->getNumCriteriaItems())
        return QVariant();

    boost::shared_ptr<CriteriaItem> ci = m_gradingCriteria->getCriteriaItem(index.row());

    switch(role)
    {
        case Qt::DisplayRole:
        case StringRole:
            return QVariant::fromValue(
                        QString::fromStdString(ci->getItemStr()));
            break;

        case LevelRole:
            return QVariant::fromValue(static_cast<int>(ci->getCriteriaItemLevel()));
            break;

        default:
            return QVariant();
            break;
    }
}


QHash<int,QByteArray> QCriteriaItemListModel::roleNames() const
{
    static QHash<int, QByteArray> roleNames;

    if (roleNames.isEmpty())
    {
        roleNames[StringRole] = "criteriaString";
        roleNames[LevelRole] = "criteriaLevel";
   }

    return roleNames;
}


void QCriteriaItemListModel::removeCriteriaItem(int row)
{
    beginRemoveRows(QModelIndex(), row, row);
    m_gradingCriteria->removeCriteriaItemAt(row);
    endRemoveRows();

    emit dataChanged(m_parentIndex);
}
