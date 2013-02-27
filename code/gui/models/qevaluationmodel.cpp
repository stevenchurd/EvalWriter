// (C) Copyright Steven Hurd 2013

#include "qevaluationmodel.h"

int QEvaluationModel::rowCount(const QModelIndex &/*parent*/) const
{
    return m_eval->getNumEvalItems();
}


QVariant QEvaluationModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (index.row() >= m_eval->getNumEvalItems())
        return QVariant();

    boost::shared_ptr<EvalItem> item = m_eval->getEvalItem(index.row());

    switch(role)
    {
        case Qt::DisplayRole:
        case StringRole:
            return QVariant::fromValue(
                        QString::fromStdString(item->getItemStr()));
            break;

        case LevelRole:
            //return QVariant::fromValue(static_cast<int>(item->getCriteriaItemLevel()));
            return QVariant();
            break;

        default:
            return QVariant();
            break;
    }

}


QHash<int,QByteArray> QEvaluationModel::roleNames() const
{
    static QHash<int, QByteArray> roleNames;

    if (roleNames.isEmpty())
    {
        roleNames[StringRole] = "evalItemString";
        roleNames[LevelRole] = "evalItemLevel";
   }

    return roleNames;

}


void QEvaluationModel::move(int srcIndex, int destIndex)
{
    if(srcIndex != destIndex)
    {
        int destRow = (srcIndex < destIndex) ? destIndex+1 : destIndex;
        if(!beginMoveRows(QModelIndex(), srcIndex, srcIndex, QModelIndex(), destRow))
           return;

        m_eval->moveEvalItem(srcIndex, destIndex);
        endMoveRows();
    }
}
