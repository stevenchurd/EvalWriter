// (C) Copyright Steven Hurd 2013

#include "qevalsetslistmodel.h"
#include "utilities/persistentdatamanager.h"
#include "qmainnavigationmodel.h"

QEvalSetsListModel::QEvalSetsListModel(QObject* parent) :
    QGenericListModel(parent)
{
    assert(QObject::connect(&PDM(), SIGNAL(evalSetDataChanged(std::string)),
                            this, SLOT(onEvalSetDataChanged(std::string))));

    assert(QObject::connect(&PDM(), SIGNAL(evalDataChanged(std::string)),
                            this, SLOT(onEvalDataChanged(std::string))));
}


QEvalSetsListModel::QEvalSetsListModel(boost::shared_ptr<EvalSet> evalSet, QObject* parent) :
    QGenericListModel(parent), m_evalSet(evalSet)
{
    assert(QObject::connect(&PDM(), SIGNAL(evalSetDataChanged(std::string)),
                            this, SLOT(onEvalSetDataChanged(std::string))));

    assert(QObject::connect(&PDM(), SIGNAL(evalDataChanged(std::string)),
                            this, SLOT(onEvalDataChanged(std::string))));
}


QVariant QEvalSetsListModel::data(const QModelIndex &index, int role) const
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

        case ProgressRole:
            return QVariant::fromValue(getProgressIndicator(index.row()));
            break;

        default:
            return QVariant();
            break;
    }
}


QHash<int,QByteArray> QEvalSetsListModel::roleNames() const
{
    static QHash<int, QByteArray> roleNames;

    if (roleNames.isEmpty())
    {
        roleNames[StringRole] = "displayString";
        roleNames[ProgressRole] = "progressLevel";
    }

    return roleNames;
}


int QEvalSetsListModel::getProgressIndicator(int row) const
{
    Eval::Progress minProgress = Eval::Complete;
    Eval::Progress maxProgress = Eval::New;
    boost::shared_ptr<EvalSet> evalSet;

    if(row < 0) return -1;

    if(m_evalSet != nullptr)
    {
        evalSet = elementAt<EvalSet>(m_evalSet->evalSetsBegin(), row);
    }
    else
    {
        evalSet = elementAt<EvalSet>(PDM().evalSetsBegin(), row);
    }

    // for each eval in the eval set, see what it's progress is.
    std::for_each(evalSet->evalsBegin(), evalSet->evalsEnd(),
                  [&minProgress, &maxProgress] (boost::shared_ptr<Eval> eval)
    {
        if(minProgress > eval->getProgress())
            minProgress = eval->getProgress();

        if(maxProgress < eval->getProgress())
            maxProgress = eval->getProgress();
    });

    // if all evals have the same progress level, the evalSet progress is that.
    // if one is less than the other, then it must be InProgress
    if(minProgress == maxProgress)
        return minProgress;
    else if(minProgress < maxProgress)
        return Eval::InProgress;

    return -1;
}


std::string QEvalSetsListModel::getItemString(int index) const
{
    if(m_evalSet == nullptr)
    {
        return elementAt<EvalSet>(PDM().evalSetsBegin(), index)->getEvalSetName();
    }
    else
    {
        return elementAt<EvalSet>(m_evalSet->evalSetsBegin(), index)->getEvalSetName();
    }
}


int QEvalSetsListModel::getNumItems() const
{
    if(m_evalSet == nullptr)
    {
        return std::distance(PDM().evalSetsBegin(), PDM().evalSetsEnd());
    }
    else
    {
        return std::distance(m_evalSet->evalSetsBegin(), m_evalSet->evalSetsEnd());
    }
}


QAbstractItemModel* QEvalSetsListModel::getNextPageFromIndex(int index)
{
    if(m_evalSet == nullptr)
    {
        return makeMainNavModel(elementAt<EvalSet>(PDM().evalSetsBegin(), index));
    }
    else
    {
        return makeMainNavModel(elementAt<EvalSet>(m_evalSet->evalSetsBegin(), index));
    }
}


QList<int> QEvalSetsListModel::getSubModelOperations()
{
    QList<int> opList;

    opList.push_back(AddEvalSet);
    opList.push_back(RemoveEvalSet);
    opList.push_back(RenameEvalSet);

    return opList;
}


void QEvalSetsListModel::addItem(QString evalSetName)
{
    beginResetModel();
    if(m_evalSet == nullptr)
    {
        // add the new eval set to the global list
        boost::shared_ptr<EvalSet> newEvalSet(new EvalSet(evalSetName.toStdString(), boost::shared_ptr<EvalSet>()));
        PDM().add(newEvalSet);
    }
    else
    {
        // otherwise add it as a sub-eval set
        boost::shared_ptr<EvalSet> newEvalSet(new EvalSet(evalSetName.toStdString(), m_evalSet));
        m_evalSet->addEvalSet(newEvalSet);
    }
    endResetModel(); // TODO replace with begin/endInsertRow
}


void QEvalSetsListModel::removeItem(int row)
{
    beginRemoveRows(QModelIndex(), row, row);
    if(m_evalSet == nullptr)
    {
        PDM().remove(iterAt<EvalSet>(PDM().evalSetsBegin(), row));
    }
    else
    {
        m_evalSet->removeEvalSet(iterAt<EvalSet>(m_evalSet->evalSetsBegin(), row));
    }
    endRemoveRows();
}


void QEvalSetsListModel::renameItem(QString evalSetName, int row)
{
    boost::shared_ptr<EvalSet> evalSet;

    if(m_evalSet == nullptr)
    {
        evalSet = elementAt<EvalSet>(PDM().evalSetsBegin(), row);
    }
    else
    {
        evalSet = elementAt<EvalSet>(m_evalSet->evalSetsBegin(), row);
    }

    evalSet->updateEvalSetName(evalSetName.toStdString());
    emit PDM().evalSetDataChanged(evalSet->getUuid());
}


QStringList QEvalSetsListModel::getOptionListForOperation(int /*operation*/)
{
    QStringList optionsList;
    assert(false); // this function should not be used for eval sets
    return optionsList;
}


void QEvalSetsListModel::optionListSelection(int /*operation*/, int /*row*/)
{
    assert(false); // this function should not be used for eval sets
}


void QEvalSetsListModel::onEvalSetDataChanged(std::string uuid)
{
    auto evalSetsBegin = PDM().evalSetsBegin();
    auto evalSetsEnd = PDM().evalSetsEnd();

    if(m_evalSet != nullptr)
    {
        evalSetsBegin = m_evalSet->evalSetsBegin();
        evalSetsEnd = m_evalSet->evalSetsEnd();
    }

    int i = 0;
    std::for_each(evalSetsBegin, evalSetsEnd,
                  [&uuid, &i, this] (boost::shared_ptr<EvalSet> evalSet)
    {
        if(evalSet->getUuid() == uuid)
        {
            emit dataChanged(index(i), index(i));
        }
        ++i;
    });
}


void QEvalSetsListModel::onEvalDataChanged(std::string uuid)
{
    // need to find out if any of the eval sets in the list contain the
    // eval.  If so, they can be updated

    auto evalSetsBegin = PDM().evalSetsBegin();
    auto evalSetsEnd = PDM().evalSetsEnd();

    if(m_evalSet != nullptr)
    {
        evalSetsBegin = m_evalSet->evalSetsBegin();
        evalSetsEnd = m_evalSet->evalSetsEnd();
    }

    int i = 0;
    std::for_each(evalSetsBegin, evalSetsEnd,
                  [&uuid, &i, this] (boost::shared_ptr<EvalSet> evalSet)
    {
        if(evalSet->containsEval(uuid))
        {
            emit dataChanged(index(i), index(i));
        }
        ++i;
    });
}


QString QEvalSetsListModel::getOperationExplanationText(int operation, int row)
{
    QString explanationString;

    boost::shared_ptr<EvalSet> evalSet;

    if(m_evalSet != nullptr && row >= 0)
    {
        evalSet = elementAt<EvalSet>(m_evalSet->evalSetsBegin(), row);
    }
    else if(row >= 0)
    {
        evalSet = elementAt<EvalSet>(PDM().evalSetsBegin(), row);
    }

    switch(operation)
    {
        case AddEvalSet:
            explanationString = QString("Enter the name of the Evaluation Set to add:");
            break;

        case RemoveEvalSet:
            if (row < 0) return QString();
            explanationString = QString("Permanently remove the Evaluation Set \"" +
                                        QString::fromStdString(evalSet->getEvalSetName()) +
                                        "\"?\nThis will not remove the contained evaluations.");
            break;

        case RenameEvalSet:
            if (row < 0) return QString();
            explanationString = QString("Permanently rename the Evaluation Set \"" +
                                        QString::fromStdString(evalSet->getEvalSetName()) +
                                        "\" to:");
            break;

        default:
            assert(false);
            break;
    }

    return explanationString;
}

