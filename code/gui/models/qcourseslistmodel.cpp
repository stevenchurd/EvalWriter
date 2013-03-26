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


QAbstractItemModel* QCoursesListModel::getSubModelFromIndex(int index)
{
    if(m_student == nullptr)
    {
        return makeSubModel(elementAt<Course>(PDM().coursesBegin(), index));
    }
    else
    {
        return makeSubModel(elementAt<Course>(m_student->coursesBegin(), index));
    }
}


QList<int> QCoursesListModel::getSubModelOperations()
{
    QList<int> opList;

    if(m_student == nullptr)
    {
        opList.push_back(AddCourse);
        opList.push_back(RemoveCourse);
        opList.push_back(RenameCourse);
    }
    else
    {
        opList.push_back(AddExistingCourseToStudent);
        opList.push_back(RemoveExistingCourseFromStudent);
    }

    return opList;
}


void QCoursesListModel::addCourse(QString courseName) const
{
    assert(m_student == nullptr);
    boost::shared_ptr<Course> newCourse(new Course(courseName.toStdString()));

    PDM().add(newCourse);
}


void QCoursesListModel::removeCourse(int index) const
{
    assert(m_student == nullptr);
    PDM().remove(iterAt<Course>(PDM().coursesBegin(), index));
}


void QCoursesListModel::renameCourse(int index, QString courseName) const
{
    assert(m_student == nullptr);
    boost::shared_ptr<Course> course = elementAt<Course>(PDM().coursesBegin(), index);
    course->updateCourseName(courseName.toStdString());
}
