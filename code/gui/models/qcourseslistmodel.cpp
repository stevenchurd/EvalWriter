// (C) Copyright Steven Hurd 2013

#include "qcourseslistmodel.h"
#include "qstudentslistmodel.h"
#include "utilities/persistentdatamanager.h"

QCoursesListModel::QCoursesListModel(QObject* parent) :
    QGenericListModel(parent)
{
}


QCoursesListModel::QCoursesListModel(boost::shared_ptr<Student> student, QObject* parent) :
    QGenericListModel(parent), m_student(student)
{
}


std::string QCoursesListModel::getItemString(int index) const
{
    if(m_student == nullptr)
    {
        return elementAt<Course>(PDM().coursesBegin(), index)->getCourseName();
    }
    else
    {
        return elementAt<Course>(m_student->coursesBegin(), index)->getCourseName();
    }
}


int QCoursesListModel::getNumItems() const
{
    if(m_student == nullptr)
    {
        return std::distance(PDM().coursesBegin(),
                             PDM().coursesEnd());
    }
    else
    {
        return std::distance(m_student->coursesBegin(),
                             m_student->coursesEnd());
    }
}
