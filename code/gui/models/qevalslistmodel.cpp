#include "qevalslistmodel.h"
#include "utilities/persistentdatamanager.h"
#include "qevaluationmodel.h"
#include "model/visitors/removeevalvisitor.h"

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

    if(m_evalSet != nullptr)
    {
        opList.push_back(AddExistingEvalToEvalSet);
        opList.push_back(RemoveEvalFromEvalSet);
        opList.push_back(RenameEval);
    }
    else if(m_student != nullptr)
    {
        opList.push_back(AddEval);
        opList.push_back(RemoveEval);
        opList.push_back(RenameEval);
    }
    else
    {
        assert(false);
    }

    return opList;
}


QStringList QEvalsListModel::getOptionListForOperation(int operation)
{
    QStringList optionsList;
    assert(false); // not used
    return optionsList;
}


void QEvalsListModel::removeItem(int row)
{
    beginRemoveRows(QModelIndex(), row, row);
    if(m_evalSet != nullptr)
    {
        // removing from an eval set just removes the eval
        m_evalSet->removeEval(iterAt<Eval>(m_evalSet->evalsBegin(), row));
    }
    else if(m_student != nullptr)
    {
        // removing an eval from a student permanently deletes it
        boost::shared_ptr<Eval> eval = elementAt<Eval>(m_student->evalsBegin(), row);
        std::vector<std::string> evalUuids;
        evalUuids.push_back(eval->getUuid());

        // need to remove the eval from all the Eval Sets too
        RemoveEvalVisitor rev(evalUuids);
        std::for_each(PDM().evalSetsBegin(), PDM().evalSetsEnd(),
                      [&rev] (boost::shared_ptr<EvalSet> evalSet)
        {
            evalSet->accept(rev);
        });

        // now remove the eval from the student
        m_student->removeEval(iterAt<Eval>(m_student->evalsBegin(), row));
    }
    else
    {
        assert(false);
    }
    endRemoveRows();
}


void QEvalsListModel::renameItem(QString newName, int row)
{
    boost::shared_ptr<Eval> eval;

    if(m_evalSet != nullptr)
    {
        eval = elementAt<Eval>(m_evalSet->evalsBegin(), row);
    }
    else if(m_student != nullptr)
    {
        eval = elementAt<Eval>(m_student->evalsBegin(), row);
    }
    else
    {
        assert(false);
    }

    eval->setEvalName(newName.toStdString());
    emit dataChanged(index(row), index(row));
}


void QEvalsListModel::optionListSelection(int operation, int row)
{
    //TODO
}


QString QEvalsListModel::getOperationExplanationText(int operation, int row)
{
    QString explanationString;
    //TODO
    return explanationString;
}
