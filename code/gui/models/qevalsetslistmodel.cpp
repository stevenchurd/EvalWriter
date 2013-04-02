// (C) Copyright Steven Hurd 2013

#include "qevalsetslistmodel.h"
#include "utilities/persistentdatamanager.h"

QEvalSetsListModel::QEvalSetsListModel(QObject* parent) :
    QGenericListModel(parent)
{
}


QEvalSetsListModel::QEvalSetsListModel(boost::shared_ptr<EvalSet> evalSet, QObject* parent) :
    QGenericListModel(parent), m_evalSet(evalSet)
{
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


QAbstractItemModel* QEvalSetsListModel::getSubModelFromIndex(int index)
{
    if(m_evalSet == nullptr)
    {
        return makeSubModel(elementAt<EvalSet>(PDM().evalSetsBegin(), index));
    }
    else
    {
        return makeSubModel(elementAt<EvalSet>(m_evalSet->evalSetsBegin(), index));
    }
}


QList<int> QEvalSetsListModel::getSubModelOperations()
{
    QList<int> opList;

    return opList;
}


void QEvalSetsListModel::addEvalSet(QString evalSetName) const
{
    boost::shared_ptr<EvalSet> newEvalSet(new EvalSet(evalSetName.toStdString()));

    if(m_evalSet == nullptr)
    {
        // add the new eval set to the global list
        PDM().add(newEvalSet);
    }
    else
    {
        // otherwise add it as a sub-eval set
        m_evalSet->addEvalSet(newEvalSet);
    }
}


void QEvalSetsListModel::removeItem(int index)
{
    if(m_evalSet == nullptr)
    {
        PDM().remove(iterAt<EvalSet>(PDM().evalSetsBegin(), index));
    }
    else
    {
        m_evalSet->removeEvalSet(iterAt<EvalSet>(m_evalSet->evalSetsBegin(), index));
    }
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
    emit dataChanged(index(row), index(row));
}

