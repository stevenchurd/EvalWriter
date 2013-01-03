#include "qevaluationmodel.h"
#if 0
int QEvaluationModel::rowCount(const QModelIndex &parent) const
{
    return m_eval->getNumEvalItems();
}


QVariant QEvaluationModel::data(const QModelIndex &index, int role) const
{
    return QVariant();
}


QVariant QEvaluationModel::headerData(int section, Qt::Orientation orientation,
                    int role) const
{
    return QVariant();
}


Qt::ItemFlags QEvaluationModel::flags(const QModelIndex &index) const
{
    return Qt::NoItemFlags;
}


bool setData(const QModelIndex &index, const QVariant &value,
             int role = Qt::EditRole)
{
    return false;
}


bool QEvaluationModel::insertRows(int row, int count, const QModelIndex &parent)
{
    return false;
}


bool QEvaluationModel::removeRows(int row, int count, const QModelIndex &parent)
{
    return false;
}
#endif
