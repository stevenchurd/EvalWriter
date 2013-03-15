// (C) Copyright Steven Hurd 2013

#include "qstudentsortfilterproxymodel.h"
#include "qstudentslistmodel.h"

QStudentSortFilterProxyModel::QStudentSortFilterProxyModel(
        boost::shared_ptr<Course> course, QObject *parent) :
    QSortFilterProxyModel(parent), m_course(course)
{
}

bool QStudentSortFilterProxyModel::filterAcceptsRow(int source_row,
                                const QModelIndex &/*source_parent*/) const
{
    QStudentsListModel* slm = dynamic_cast<QStudentsListModel*>(sourceModel());
    boost::shared_ptr<Student> student = slm->getStudent(source_row);

    return student->isInCourse(m_course);
}
