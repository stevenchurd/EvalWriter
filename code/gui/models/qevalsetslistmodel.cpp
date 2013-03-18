// (C) Copyright Steven Hurd 2013

#include "qevalsetslistmodel.h"
#include "utilities/persistentdatamanager.h"

QEvalSetsListModel::QEvalSetsListModel(QObject* parent) :
    QGenericListModel(parent)
{
}


std::string QEvalSetsListModel::getItemString(int index) const
{
    return elementAt<EvalSet>(PDM().evalSetsBegin(), index)->getEvalSetName();
}


int QEvalSetsListModel::getNumItems() const
{
    return std::distance(PDM().evalSetsBegin(), PDM().evalSetsEnd());
}
