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
