#include "qmainnavigationmodel.h"
#include "qgenericlistmodel.h"
#include "qcourseslistmodel.h"
#include "qevalslistmodel.h"
#include "qstudentslistmodel.h"
#include "qevalsetslistmodel.h"
#include "utilities/persistentdatamanager.h"

QMainNavigationModel::QMainNavigationModel(std::string uuidForTitle, QObject *parent) :
    QAbstractListModel(parent), m_uuidForTitle(uuidForTitle)
{
}


QObject* QMainNavigationModel::getSubModel(int index) const
{
    if(index > static_cast<int>(m_submodels.size()) || index < 0)
        return nullptr;

    return static_cast<QObject*>(std::get<1>(m_submodels[index]));
}


int QMainNavigationModel::getSubModelType(int index) const
{
    if(index > static_cast<int>(m_submodels.size()) || index < 0)
        return -1;

    return static_cast<int>(std::get<2>(m_submodels[index]));
}


QString QMainNavigationModel::getModelTitle() const
{
    return QString::fromStdString(getDisplayableTitleFromUuid(m_uuidForTitle));
}


void QMainNavigationModel::addSubModel(std::string displayString, QAbstractItemModel* listModel, QGenericListModel::SubModelType modelType)
{
    // reparent model
    listModel->setParent(this);
    m_submodels.push_back(std::make_tuple(displayString, listModel, modelType));
}


int QMainNavigationModel::rowCount(const QModelIndex &/*parent*/) const
{
    return static_cast<int>(m_submodels.size());
}


QVariant QMainNavigationModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (index.row() >= static_cast<int>(m_submodels.size()))
        return QVariant();

    switch(role)
    {
        case Qt::DisplayRole:
        case StringRole:
            return QVariant::fromValue(
                        QString::fromStdString(std::get<0>(m_submodels[index.row()])));
            break;

        case SubModelTypeRole:
            return QVariant::fromValue(static_cast<int>(std::get<2>(m_submodels[index.row()])));
            break;

        default:
            return QVariant();
            break;
    }

}


QHash<int,QByteArray> QMainNavigationModel::roleNames() const
{
    static QHash<int, QByteArray> roleNames;

    if (roleNames.isEmpty())
    {
        roleNames[StringRole] = "submodelName";
        roleNames[SubModelTypeRole] = "submodelType";
    }

    return roleNames;
}


//
// Non-class/non-friend helper functions
//
std::string getDisplayableTitleFromUuid(std::string uuid)
{
    if(uuid.empty())
        return std::string();

    // need to find the item with the associated UUID
    boost::shared_ptr<Student> student;
    if(PDM().getItemByUuid(uuid, student))
    {
        return student->getDisplayName();
    }

    boost::shared_ptr<Course> course;
    if(PDM().getItemByUuid(uuid, course))
    {
        return course->getCourseName();
    }

    boost::shared_ptr<EvalSet> evalSet;
    if(PDM().getItemByUuid(uuid, evalSet))
    {
        return evalSet->getEvalSetName();
    }

    // nothing found, return a string indicating an error
    assert(false);
    throw ItemNotFoundException("Item not found with UUID: " + uuid);
}


QAbstractItemModel* makeMainNavModel(boost::shared_ptr<Student> student)
{
    QMainNavigationModel* navModel = new QMainNavigationModel(student->getUuid());

    QCoursesListModel* coursesList = new QCoursesListModel(student);
    QEvalsListModel* evalsList = new QEvalsListModel(student);

    navModel->addSubModel("Classes", coursesList, QGenericListModel::CourseList);
    navModel->addSubModel("Evaluations", evalsList, QGenericListModel::EvaluationList);

    return navModel;
}


QAbstractItemModel* makeMainNavModel(boost::shared_ptr<Course> course)
{
    QMainNavigationModel* navModel = new QMainNavigationModel(course->getUuid());

    QStudentsListModel* studentsList = new QStudentsListModel(course);

    navModel->addSubModel("Students", studentsList, QGenericListModel::StudentList);

    return navModel;
}


QAbstractItemModel* makeMainNavModel(boost::shared_ptr<EvalSet> evalSet)
{
    QMainNavigationModel* navModel = new QMainNavigationModel(evalSet->getUuid());

    QEvalsListModel* evalsList = new QEvalsListModel(evalSet);
    QEvalSetsListModel* evalSetsList = new QEvalSetsListModel(evalSet);

    navModel->addSubModel("Evaluations", evalsList, QGenericListModel::EvaluationList);
    navModel->addSubModel("Evaluation Sets", evalSetsList, QGenericListModel::EvalSetList);

    return navModel;
}

