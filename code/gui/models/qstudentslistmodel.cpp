#include "qstudentslistmodel.h"

QStudentsListModel::QStudentsListModel(QVector<boost::shared_ptr<Student> >& students, QObject* parent) :
    QGenericListModel(parent), m_students(students)
{
}


boost::shared_ptr<QMainNavigationModel> QStudentsListModel::constructMainNavigationModel(int index) const
{
    //TODO: correct
    return boost::shared_ptr<QMainNavigationModel>(new QMainNavigationModel());
}


std::string QStudentsListModel::getItemString(int index) const
{
    return m_students[index]->getFirstName() + " " + m_students[index]->getMiddleName() + " " + m_students[index]->getLastName();
}


int QStudentsListModel::getNumItems() const
{
    return m_students.size();
}
