#include "qevalslistmodel.h"

QEvalsListModel::QEvalsListModel(QVector<boost::shared_ptr<Eval> >& evals, QObject* parent) :
    QGenericListModel(parent), m_evals(evals)
{
}


std::string QEvalsListModel::getItemString(int index) const
{
    return m_evals[index]->getEvalName();
}


int QEvalsListModel::getNumItems() const
{
    return m_evals.size();
}
