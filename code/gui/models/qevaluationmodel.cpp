// (C) Copyright Steven Hurd 2013

#include "qevaluationmodel.h"
#include "model/eval.h"
#include "model/gradingcriteria.h"
#include "model/customtextitem.h"

#include "utilities/persistentdatamanager.h"

QEvaluationModel::QEvaluationModel(boost::shared_ptr<Eval> eval,
                 QObject* parent) :
    QAbstractListModel(parent), m_eval(eval)
{
}


QString QEvaluationModel::getEvalTitle() const
{
    return QString::fromStdString(m_eval->getEvalName());
}


QString QEvaluationModel::getFullEvalText() const
{
    std::stringstream ss;
    m_eval->getPrintableEvalString(ss);
    return QString::fromStdString(ss.str());
}


int QEvaluationModel::isEvalComplete() const
{
    return (m_eval->getProgress() == Eval::Complete);
}


void QEvaluationModel::toggleEvalComplete() const
{
    if(m_eval->getProgress() == Eval::Complete)
        m_eval->setProgressInProgress();
    else
        m_eval->setProgressCompleted();

    emit PDM().evalDataChanged(m_eval->getUuid());
}


int QEvaluationModel::rowCount(const QModelIndex &/*parent*/) const
{
    return m_eval->getNumEvalItems();
}


QVariant QEvaluationModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (index.row() >= static_cast<int>(m_eval->getNumEvalItems()))
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

        case InPlaceEditableRole:
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
        roleNames[InPlaceEditableRole] = "evalItemIsEditable";
   }

    return roleNames;
}



void QEvaluationModel::addCustomTextItem(QString title, QString customText)
{
    beginInsertRows(QModelIndex(), m_eval->getNumEvalItems(), m_eval->getNumEvalItems());
    boost::shared_ptr<EvalItem> cti(new CustomTextItem(title.toStdString(), customText.toStdString()));
    m_eval->addEvalItem(cti);
    m_eval->setProgressInProgress();
    emit PDM().evalDataChanged(m_eval->getUuid());
    endInsertRows();
}


void QEvaluationModel::addCriteriaItem(int destIndex, QString uuid)
{
    boost::shared_ptr<CriteriaItem> item;
    PDM().getItemByUuid(uuid.toStdString(), item);

    assert(item != nullptr);

    if(destIndex <= static_cast<int>(m_eval->getNumEvalItems()))
    {
        beginInsertRows(QModelIndex(), destIndex, destIndex);
        m_eval->addEvalItemAt(destIndex, item);
        m_eval->setProgressInProgress();
        emit PDM().evalDataChanged(m_eval->getUuid());
        endInsertRows();
    }
}


void QEvaluationModel::moveEvalItem(int srcIndex, int destIndex)
{
    if(srcIndex != destIndex)
    {
        int destRow = (srcIndex < destIndex) ? destIndex+1 : destIndex;
        if(!beginMoveRows(QModelIndex(), srcIndex, srcIndex, QModelIndex(), destRow))
           return;

        m_eval->moveEvalItem(srcIndex, destIndex);
        m_eval->setProgressInProgress();
        emit PDM().evalDataChanged(m_eval->getUuid());
        endMoveRows();
    }
}


void QEvaluationModel::removeItem(int row)
{
    beginRemoveRows(QModelIndex(), row, row);
    deselectItem(row);
    m_eval->removeEvalItemAt(row);
    m_eval->setProgressInProgress();
    emit PDM().evalDataChanged(m_eval->getUuid());
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


void QEvaluationModel::editItemString(int row, QString title, QString string)
{
    boost::shared_ptr<EvalItem> ei = m_eval->getEvalItem(row);
    if(ei->isItemEditable())
{
        ei->setItemStr(string.toStdString());
        ei->setItemTitleStr(title.toStdString());
        emit dataChanged(index(row), index(row));
    }
}


// operation interface
QList<int> QEvaluationModel::getSubModelOperations()
{
    QList<int> opList;
    opList.push_back(AddCustomTextItem);
    return opList;
}


QString QEvaluationModel::getOperationExplanationText(int operation, int /*row*/)
{
    QString explanationText;

    switch(operation)
    {
        case AddCustomTextItem:
            explanationText = QString("Enter the custom text item below:");

            break;

        default:
            assert(false);
            break;
    }

    return explanationText;
}
