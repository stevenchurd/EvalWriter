// (C) Copyright Steven Hurd 2013

#include "qevaluationmodel.h"
#include "model/gradingcriteria.h"

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
            return QVariant::fromValue(
                        static_cast<int>(item->getItemLevel()));
            break;

        case SelectedRole:
            return QVariant::fromValue(
                        (std::find(m_selected.begin(), m_selected.end(), index.row()) != m_selected.end()));
            break;

        case TitleRole:
            return QVariant::fromValue(
                        QString::fromStdString(item->getItemTitleStr()));
            break;

        case InPlaceEditable:
            return QVariant::fromValue(item->isItemEditable());
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
        roleNames[SelectedRole] = "evalItemSelected";
        roleNames[TitleRole] = "evalItemTitle";
        roleNames[InPlaceEditable] = "evalItemIsEditable";
   }

    return roleNames;
}


void QEvaluationModel::addCriteriaItem(int destIndex, int uniqueId)
{
    boost::shared_ptr<CriteriaItem> item;

    for(auto it = m_gradingCriteria.begin(); it != m_gradingCriteria.end(); ++it)
    {
        if((*it)->getCriteriaItemById(uniqueId, item) == true)
        {
            break;
        }
    }

    if(destIndex <= m_eval->getNumEvalItems())
    {
        beginInsertRows(QModelIndex(), destIndex, destIndex);
        m_eval->addEvalItemAt(destIndex, item);
        endInsertRows();
    }
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


void QEvaluationModel::removeItem(int row)
{
    beginRemoveRows(QModelIndex(), row, row);
    deselectItem(row);
    m_eval->removeEvalItemAt(row);
    endRemoveRows();
}


void QEvaluationModel::selectItem(int row)
{
    m_selected.push_back(row);
    emit dataChanged(index(row), index(row));
}


void QEvaluationModel::deselectItem(int row)
{
    auto eraseList = std::remove_if(m_selected.begin(), m_selected.end(),
                                    std::bind1st(std::equal_to<int>(), row));

    m_selected.erase(eraseList, m_selected.end());
    emit dataChanged(index(row), index(row));
}


void QEvaluationModel::deselectAllItems(void)
{
    m_selected.clear();
    emit dataChanged(index(0), index(m_eval->getNumEvalItems()-1));
}


void QEvaluationModel::editItemString(int row, QString string)
{
    boost::shared_ptr<EvalItem> ei = m_eval->getEvalItem(row);
    if(ei->isItemEditable())
{
        ei->setItemStr(string.toStdString());
        emit dataChanged(index(row), index(row));
    }
}
