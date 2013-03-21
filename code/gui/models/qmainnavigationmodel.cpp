#include "qmainnavigationmodel.h"
#include "qgenericlistmodel.h"
#include "qcourseslistmodel.h"
#include "qevalslistmodel.h"
#include "qstudentslistmodel.h"
#include "qevalsetslistmodel.h"


QMainNavigationModel::QMainNavigationModel(QObject *parent) :
    QAbstractListModel(parent)
{
}

QObject* QMainNavigationModel::getSubModel(int index) const
{
    if(index > static_cast<int>(m_submodels.size()) || index < 0)
        return nullptr;

    return static_cast<QObject*>(std::get<1>(m_submodels[index]));
}


void QMainNavigationModel::addSubModel(std::string displayString, QAbstractItemModel* listModel)
{
    // reparent model
    listModel->setParent(this);
    m_submodels.push_back(std::make_tuple(displayString, listModel));
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
    }

    return roleNames;
}


QAbstractItemModel* makeSubModel(boost::shared_ptr<Student> student)
{
    QMainNavigationModel* navModel = new QMainNavigationModel();

    QCoursesListModel* coursesList = new QCoursesListModel(student);
    QEvalsListModel* evalsList = new QEvalsListModel(student);

    navModel->addSubModel("Classes", coursesList);
    navModel->addSubModel("Evaluations", evalsList);

    return navModel;
}


QAbstractItemModel* makeSubModel(boost::shared_ptr<Course> course)
{
    QMainNavigationModel* navModel = new QMainNavigationModel();

    QStudentsListModel* studentsList = new QStudentsListModel(course);

    navModel->addSubModel("Students", studentsList);

    return navModel;
}


QAbstractItemModel* makeSubModel(boost::shared_ptr<EvalSet> evalSet)
{
    QMainNavigationModel* navModel = new QMainNavigationModel();

    QEvalsListModel* evalsList = new QEvalsListModel(evalSet);
    QEvalSetsListModel* evalSetsList = new QEvalSetsListModel(evalSet);

    navModel->addSubModel("Evaluations", evalsList);
    navModel->addSubModel("Evaluation Sets", evalSetsList);

    return navModel;
}

