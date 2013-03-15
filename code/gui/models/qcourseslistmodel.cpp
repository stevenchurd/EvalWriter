// (C) Copyright Steven Hurd 2013

#include "qcourseslistmodel.h"
#include "qstudentsortfilterproxymodel.h"
#include "qstudentslistmodel.h"

QCoursesListModel::QCoursesListModel(QVector<boost::shared_ptr<Course> >& courses,
                  QVector<boost::shared_ptr<Student> >& globalStudents,
                  QObject* parent) :
    QGenericListModel(parent), m_courses(courses), m_students(globalStudents)
{
}


boost::shared_ptr<QMainNavigationModel> QCoursesListModel::constructMainNavigationModel(int index) const
{
    QStudentSortFilterProxyModel* proxyModel = new QStudentSortFilterProxyModel(m_courses[index]);
    QStudentsListModel* studentListModel = new QStudentsListModel(m_students);
    proxyModel->setSourceModel(studentListModel);

    boost::shared_ptr<QMainNavigationModel> navModel(new QMainNavigationModel());
    navModel->addSubModel("Students", proxyModel);

    return navModel;
}


std::string QCoursesListModel::getItemString(int index) const
{
    return m_courses[index]->getCourseName();
}


int QCoursesListModel::getNumItems() const
{
    return m_courses.size();
}
