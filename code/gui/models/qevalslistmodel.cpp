#include <set>

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


int QEvalsListModel::getProgressIndicator(int row) const
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

    return eval->getProgress();
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


QAbstractItemModel* QEvalsListModel::getNextPageFromIndex(int index)
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

    switch(operation)
    {
        case AddExistingEvalToEvalSet:
        {
            assert(m_evalSet != nullptr);
            // these are the Evals of an Eval Set so to add evals, show
            // the evals of the parent eval
            boost::shared_ptr<EvalSet> parentEvalSet = m_evalSet->getParentEvalSet();
            std::set<boost::shared_ptr<Eval> > parentEvals;
            std::set<boost::shared_ptr<Eval> > currentEvals(
                        m_evalSet->evalsBegin(), m_evalSet->evalsEnd());

            if(parentEvalSet == nullptr)
            {
                // need to get all existing evals in students
                std::for_each(PDM().studentsBegin(), PDM().studentsEnd(),
                              [&parentEvals] (boost::shared_ptr<Student> student)
                {
                    parentEvals.insert(student->evalsBegin(), student->evalsEnd());
                });

            }
            else
            {
                parentEvals = std::set<boost::shared_ptr<Eval> >(
                            parentEvalSet->evalsBegin(), parentEvalSet->evalsEnd());
            }

            std::vector<boost::shared_ptr<Eval> > evals;
            std::set_difference(parentEvals.begin(), parentEvals.end(),
                                currentEvals.begin(), currentEvals.end(),
                                std::inserter(evals, evals.begin()));
            std::sort(evals.begin(), evals.end());

            std::for_each(evals.begin(), evals.end(),
                          [&optionsList] (boost::shared_ptr<Eval> eval)
            {
                optionsList.push_back(QString::fromStdString(eval->getEvalName()));
            });
        }
            break;

        default:
            assert(false);
            break;
    }

    return optionsList;
}


void QEvalsListModel::addItem(QString newEvalName)
{
    beginResetModel();
    assert(m_student != nullptr && m_evalSet == nullptr);
    boost::shared_ptr<Eval> newEval(new Eval(newEvalName.toStdString(), Eval::New));
    m_student->addEval(newEval);
    endResetModel(); // TODO: replace with beginInsertRow
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
    if(row < 0)
    {
        return;
    }

    switch(operation)
    {
        case AddExistingEvalToEvalSet:
        {
            assert(m_evalSet != nullptr);
            // these are the Evals of an Eval Set so to add evals, show
            // the evals of the parent eval
            boost::shared_ptr<EvalSet> parentEvalSet = m_evalSet->getParentEvalSet();
            std::set<boost::shared_ptr<Eval> > parentEvals;
            std::set<boost::shared_ptr<Eval> > currentEvals(
                        m_evalSet->evalsBegin(), m_evalSet->evalsEnd());

            if(parentEvalSet == nullptr)
            {
                // need to get all existing evals in students
                std::for_each(PDM().studentsBegin(), PDM().studentsEnd(),
                              [&parentEvals] (boost::shared_ptr<Student> student)
                {
                    parentEvals.insert(student->evalsBegin(), student->evalsEnd());
                });

            }
            else
            {
                parentEvals = std::set<boost::shared_ptr<Eval> >(
                            parentEvalSet->evalsBegin(), parentEvalSet->evalsEnd());
            }

            std::vector<boost::shared_ptr<Eval> > evals;
            std::set_difference(parentEvals.begin(), parentEvals.end(),
                                currentEvals.begin(), currentEvals.end(),
                                std::inserter(evals, evals.begin()));
            std::sort(evals.begin(), evals.end());

            // now that we have the list, add the selected course to the student
            if(row < static_cast<int>(evals.size()))
            {
                beginResetModel(); // TODO eventually replace this with a beginInsertRows
                m_evalSet->addEval(evals[row]);
                endResetModel();
            }
       }
            break;

        default:
            assert(false);
            break;
    }
}


QString QEvalsListModel::getOperationExplanationText(int operation, int row)
{
    QString explanationString;

    switch(operation)
    {
        case AddEval:
            explanationString = QString("Enter the name of the evaluation to add:");
            break;

        case AddExistingEvalToEvalSet:
            assert(m_evalSet != nullptr);
            explanationString = QString("Select an evaluation to add to the set:");
            break;

        case RemoveEval:
            assert(m_student != nullptr);
            if (row < 0) return QString();
            explanationString = QString("Remove the evaluation \"" +
                                        QString::fromStdString(elementAt<Eval>(m_student->evalsBegin(), row)->getEvalName()) +
                                        "\"?");
            break;

        case RemoveEvalFromEvalSet:
            assert(m_evalSet != nullptr);
            if (row < 0) return QString();
            explanationString = QString("Remove the evaluation \"" +
                                        QString::fromStdString(elementAt<Eval>(m_evalSet->evalsBegin(), row)->getEvalName()) +
                                        "\" from this set?");
            break;

        case RenameEval:
        {
            if (row < 0) return QString();
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
            explanationString = QString("Permanently rename the evaluation \"" +
                                        QString::fromStdString(eval->getEvalName()) +
                                        "\" to:");
        }
            break;

        default:
            assert(false);
            break;
    }

    return explanationString;
}
