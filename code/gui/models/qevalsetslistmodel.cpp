// (C) Copyright Steven Hurd 2013

#include "qevalsetslistmodel.h"


QEvalSetsListModel::QEvalSetsListModel(QVector<boost::shared_ptr<EvalSet> >& evalsets, QObject* parent) :
    QGenericListModel(parent), m_evalsets(evalsets)
{
}


std::string QEvalSetsListModel::getItemString(int index) const
{
    return m_evalsets[index]->getEvalSetName();
}


int QEvalSetsListModel::getNumItems() const
{
    return m_evalsets.size();
}
