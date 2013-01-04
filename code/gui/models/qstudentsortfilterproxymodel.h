// (C) Copyright Steven Hurd 2013

#ifndef QSTUDENTSORTFILTERPROXYMODEL_H
#define QSTUDENTSORTFILTERPROXYMODEL_H

#include <QSortFilterProxyModel>

#include <boost/shared_ptr.hpp>

#include "model/course.h"

class QStudentSortFilterProxyModel : public QSortFilterProxyModel
{
public:
    QStudentSortFilterProxyModel(boost::shared_ptr<Course> course,
                                 QObject* parent = 0);
    virtual ~QStudentSortFilterProxyModel() {}

    virtual bool filterAcceptsRow(int source_row,
                                  const QModelIndex &source_parent) const;

private:
    boost::shared_ptr<Course> m_course;
};

#endif // QSTUDENTSORTFILTERPROXYMODEL_H
