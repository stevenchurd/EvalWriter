// (C) Copyright Steven Hurd 2013

#include "qcourseslistmodel.h"


QCoursesListModel::QCoursesListModel(QVector<boost::shared_ptr<Course> >& courses, QObject* parent) :
    QGenericListModel(parent), m_courses(courses)
{
}


std::string QCoursesListModel::getItemString(int index) const
{
    return m_courses[index]->getCourseName();
}


int QCoursesListModel::getNumItems() const
{
    return m_courses.size();
}
