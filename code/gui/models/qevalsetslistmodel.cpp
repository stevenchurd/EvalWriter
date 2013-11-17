// (C) Copyright Steven Hurd 2013

#include "qevalsetslistmodel.h"
#include "model/eval.h"
#include "utilities/persistentdatamanager.h"
#include "qmainnavigationmodel.h"

QEvalSetsListModel::QEvalSetsListModel(QObject* parent) :
    QGenericListModel(parent)
{
    QObject::connect(&PDM(), SIGNAL(evalSetDataChanged(std::string)),
                            this, SLOT(onEvalSetDataChanged(std::string)));

    QObject::connect(&PDM(), SIGNAL(evalDataChanged(std::string)),
                            this, SLOT(onEvalDataChanged(std::string)));
}


QEvalSetsListModel::QEvalSetsListModel(boost::shared_ptr<EvalSet> evalSet, QObject* parent) :
    QGenericListModel(parent), m_evalSet(evalSet)
{
    QObject::connect(&PDM(), SIGNAL(evalSetDataChanged(std::string)),
                            this, SLOT(onEvalSetDataChanged(std::string)));

    QObject::connect(&PDM(), SIGNAL(evalDataChanged(std::string)),
                            this, SLOT(onEvalDataChanged(std::string)));
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
        return EvalSetInProgress;
    else if(minProgress > maxProgress)
        return EvalSetEmpty;

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

    // if this is the root menu, allow these options
    if(m_evalSet == nullptr)
    {
        // only allow the options if a a Course or Eval set exists
        if(PDM().coursesBegin() != PDM().coursesEnd())
        {
            opList.push_back(CreateEvalSetFromCourse);
        }

        if(PDM().evalSetsBegin() != PDM().evalSetsEnd())
        {
            opList.push_back(CreateEvalSetFromEvalSet);
        }
    }

    opList.push_back(AddEvalSet);
    opList.push_back(RemoveEvalSet);
    opList.push_back(RenameEvalSet);

    return opList;
}


void QEvalSetsListModel::addItem(QString evalSetName)
{
    if(m_evalSet == nullptr)
    {
        // add the new eval set to the global list
        boost::shared_ptr<EvalSet> newEvalSet(new EvalSet(evalSetName.toStdString(), boost::shared_ptr<EvalSet>()));

        unsigned int newRow = insertLocation(newEvalSet,
                                             PDM().evalSetsBegin(),
                                             PDM().evalSetsEnd());
        beginInsertRows(QModelIndex(), newRow, newRow);
        PDM().add(newEvalSet);
        endInsertRows();
    }
    else
    {
        // otherwise add it as a sub-eval set
        boost::shared_ptr<EvalSet> newEvalSet(new EvalSet(evalSetName.toStdString(), m_evalSet));

        unsigned int newRow = insertLocation(newEvalSet,
                                             m_evalSet->evalSetsBegin(),
                                             m_evalSet->evalSetsEnd());
        beginInsertRows(QModelIndex(), newRow, newRow);
        m_evalSet->addEvalSet(newEvalSet);
        endInsertRows();
    }
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


QStringList QEvalSetsListModel::getOptionListForOperation(int operation)
{
    QStringList optionsList;

    assert(m_evalSet == nullptr);

    switch(operation)
    {
        case CreateEvalSetFromCourse:
            std::for_each(PDM().coursesBegin(), PDM().coursesEnd(),
                          [&optionsList] (boost::shared_ptr<Course> course)
            {
                optionsList.push_back(QString::fromStdString(course->getCourseName()));
            });
            break;

        case CreateEvalSetFromEvalSet:
            std::for_each(PDM().evalSetsBegin(), PDM().evalSetsEnd(),
                          [&optionsList] (boost::shared_ptr<EvalSet> evalSet)
            {
                optionsList.push_back(QString::fromStdString(evalSet->getEvalSetName()));
            });
            break;

        default:
            assert(false);
            break;
    }

    return optionsList;
}


void QEvalSetsListModel::optionListSelection(int /*operation*/, int /*row*/)
{
    assert(false); // this function should not be used for eval sets
}


void QEvalSetsListModel::createEvalSet(int selectedItem, int operation, QString evalSetName, QString evalPrefix)
{
    assert(selectedItem >= 0);
    assert(!evalSetName.isEmpty() && !evalPrefix.isEmpty());

    boost::shared_ptr<EvalSet> newEvalSet;

    switch(operation)
    {
        case CreateEvalSetFromCourse:
            newEvalSet = createEvalSetFromCourse(elementAt<Course>(PDM().coursesBegin(), selectedItem),
                                    evalSetName.toStdString(),
                                    evalPrefix.toStdString());
            break;

        case CreateEvalSetFromEvalSet:
            newEvalSet = createEvalSetFromEvalSet(elementAt<EvalSet>(PDM().evalSetsBegin(), selectedItem),
                                     evalSetName.toStdString(),
                                     evalPrefix.toStdString());
            break;

        default:
            assert(false);
            break;
    }

    unsigned int newRow = insertLocation(newEvalSet,
                                         PDM().evalSetsBegin(),
                                         PDM().evalSetsEnd());
    beginInsertRows(QModelIndex(), newRow, newRow);
    PDM().add(newEvalSet);
    endInsertRows();

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

        case CreateEvalSetFromCourse:
            explanationString = QString("Create an Evaluation Set from a class.  This will create a new Evaluation Set with a new evaluation for each student in the class.");
            break;

        case CreateEvalSetFromEvalSet:
            explanationString = QString("Create an Evaluation Set from a previous evaluation.  This will create a new Evaluation Set with a new copy of each contained Evaluation from the original set.");
            break;

        default:
            assert(false);
            break;
    }

    return explanationString;
}



boost::shared_ptr<EvalSet> createEvalSetFromEvalSet(boost::shared_ptr<EvalSet> oldSet,
                                                    std::string evalSetName,
                                                    std::string evalNamePrefix)
{
    boost::shared_ptr<EvalSet> newSet(new EvalSet(evalSetName, boost::shared_ptr<EvalSet>()));


    std::for_each(oldSet->evalsBegin(), oldSet->evalsEnd(),
                  [&newSet, &evalSetName, &evalNamePrefix] (boost::shared_ptr<Eval> eval)
    {
        boost::shared_ptr<Student> student = *(std::find_if(PDM().studentsBegin(), PDM().studentsEnd(),
                                                          [&eval] (boost::shared_ptr<Student> student)
                                                        { return student->hasEval(eval->getUuid()); }));

        // evalNamePrefix: StudentDisplayName
        std::string evalName(evalNamePrefix + ": " + student->getDisplayName());
        boost::shared_ptr<Eval> newEval(new Eval(evalName, *eval));

        // now add the eval to both the student and the eval set
        student->addEval(newEval);
        newSet->addEval(newEval);
    });

    return newSet;
}


boost::shared_ptr<EvalSet> createEvalSetFromCourse(boost::shared_ptr<Course> course,
                                                   std::string evalSetName,
                                                   std::string evalNamePrefix)
{
    boost::shared_ptr<EvalSet> newSet(new EvalSet(evalSetName, boost::shared_ptr<EvalSet>()));

    // for each student in the course, we need to create a new Eval and add it to them.
    unsigned int i = 0;
    boost::shared_ptr<Student> student = getNthStudentInCourse(i, course);

    while(student != nullptr)
    {
        // the new eval name will always be of the format:
        // evalNamePrefix: StudentDisplayName
        std::string evalName(evalNamePrefix + ": " + student->getDisplayName());
        boost::shared_ptr<Eval> newEval(new Eval(evalName, Eval::New));

        // now add the eval to both the student and the eval set
        student->addEval(newEval);
        newSet->addEval(newEval);

        ++i;
        student = getNthStudentInCourse(i, course);
    }

    return newSet;
}

