#include "qmainnavigationmodel.h"
#include "qgenericlistmodel.h"
#include "qcourseslistmodel.h"
#include "qevalslistmodel.h"
#include "qstudentslistmodel.h"
#include "qevalsetslistmodel.h"


QMainNavigationModel::QMainNavigationModel(QString modelTitle, QObject *parent) :
    QAbstractListModel(parent), m_modelTitle(modelTitle)
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
    return m_modelTitle;
}


void QMainNavigationModel::addSubModel(std::string displayString, QAbstractItemModel* listModel, ModelTypes::SubModelType modelType)
{
    // reparent model
    listModel->setParent(this);
    m_submodels.push_back(std::make_tuple(displayString, listModel, modelType));
}


int QMainNavigationModel::rowCount(const QModelIndex &/*parent*/) const
{
    return m_submodels.size();
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


QAbstractItemModel* makeSubModel(boost::shared_ptr<Student> student)
{
    QMainNavigationModel* navModel = new QMainNavigationModel(
                QString::fromStdString(student->getDisplayName()));

    QCoursesListModel* coursesList = new QCoursesListModel(student);
    QEvalsListModel* evalsList = new QEvalsListModel(student);

    navModel->addSubModel("Classes", coursesList, ModelTypes::CourseList);
    navModel->addSubModel("Evaluations", evalsList, ModelTypes::EvaluationList);

    return navModel;
}


QAbstractItemModel* makeSubModel(boost::shared_ptr<Course> course)
{
    QMainNavigationModel* navModel = new QMainNavigationModel(
                QString::fromStdString(course->getCourseName()));

    QStudentsListModel* studentsList = new QStudentsListModel(course);

    navModel->addSubModel("Students", studentsList, ModelTypes::StudentList);

    return navModel;
}


QAbstractItemModel* makeSubModel(boost::shared_ptr<EvalSet> evalSet)
{
    QMainNavigationModel* navModel = new QMainNavigationModel(
                QString::fromStdString(evalSet->getEvalSetName()));

    QEvalsListModel* evalsList = new QEvalsListModel(evalSet);
    QEvalSetsListModel* evalSetsList = new QEvalSetsListModel(evalSet);

    navModel->addSubModel("Evaluations", evalsList, ModelTypes::EvaluationList);
    navModel->addSubModel("Evaluation Sets", evalSetsList, ModelTypes::EvalSetList);

    return navModel;
}

