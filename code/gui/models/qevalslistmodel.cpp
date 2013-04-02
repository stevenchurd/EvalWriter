#include "qevalslistmodel.h"
#include "utilities/persistentdatamanager.h"
#include "qevaluationmodel.h"

QEvalsListModel::QEvalsListModel(boost::shared_ptr<Student> student, QObject* parent) :
    QGenericListModel(parent), m_student(student)
{
}

QEvalsListModel::QEvalsListModel(boost::shared_ptr<EvalSet> evalSet, QObject* parent) :
    QGenericListModel(parent), m_evalSet(evalSet)
{
}


std::string QEvalsListModel::getItemString(int index) const
{
    if(m_student != nullptr)
    {
        return elementAt<Eval>(m_student->evalsBegin(), index)->getEvalName();
    }
    else if(m_evalSet != nullptr)
    {
        return elementAt<Eval>(m_evalSet->evalsBegin(), index)->getEvalName();
    }

    assert(false); //neither m_student or m_evalSet was valid
    throw GenericModelException("neither m_student or m_evalSet was valid");
}


int QEvalsListModel::getNumItems() const
{
    if(m_student != nullptr)
    {
        return m_student->getNumEvals();
    }
    else if(m_evalSet != nullptr)
    {
        return std::distance(m_evalSet->evalsBegin(), m_evalSet->evalsEnd());
    }

    assert(false); //neither m_student or m_evalSet was valid
    throw GenericModelException("neither m_student or m_evalSet was valid");
}


QAbstractItemModel* QEvalsListModel::getSubModelFromIndex(int index)
{
    if(m_student != nullptr)
    {
        return new QEvaluationModel(elementAt<Eval>(m_student->evalsBegin(), index));
    }
    else if(m_evalSet != nullptr)
    {
        return new QEvaluationModel(elementAt<Eval>(m_evalSet->evalsBegin(), index));
    }

    assert(false); //neither m_student or m_evalSet was valid
    throw GenericModelException("neither m_student or m_evalSet was valid");
}


QList<int> QEvalsListModel::getSubModelOperations()
{
    QList<int> opList;

    return opList;
}


void QEvalsListModel::removeItem(int index)
{
    //TODO
}


void QEvalsListModel::renameItem(QString newName, int row)
{
    //TODO
}
