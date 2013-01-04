// (C) Copyright Steven Hurd 2013

#include "qstudentsortfilterproxymodel.h"

#include <QStringList>

#include <boost/foreach.hpp>

QStudentSortFilterProxyModel::QStudentSortFilterProxyModel(
        boost::shared_ptr<Course> course, QObject *parent) :
    QSortFilterProxyModel(parent), m_course(course)
{
}

bool QStudentSortFilterProxyModel::filterAcceptsRow(int source_row,
                                const QModelIndex &source_parent) const
{
    QVariant qv = sourceModel()->data(sourceModel()->index(source_row, 3, source_parent));

    QStringList courses = qv.toStringList();
    BOOST_FOREACH(QString course, courses)
    {
        if(course.toStdString() == m_course->getCourseName())
        {
            return true;
        }
    }
    return false;
}
