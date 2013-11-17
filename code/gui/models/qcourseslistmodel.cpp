// (C) Copyright Steven Hurd 2013

#include <set>

#include "qcourseslistmodel.h"
#include "qstudentslistmodel.h"
#include "utilities/persistentdatamanager.h"
#include "qmainnavigationmodel.h"

#ifndef Q_MOC_RUN
#include <boost/iterator/indirect_iterator.hpp>
#endif

QCoursesListModel::QCoursesListModel(QObject* parent) :
    QGenericListModel(parent)
{
    QObject::connect(&PDM(), SIGNAL(courseDataChanged(std::string)),
                            this, SLOT(onCourseDataChanged(std::string)));
}


QCoursesListModel::QCoursesListModel(boost::shared_ptr<Student> student, QObject* parent) :
    QGenericListModel(parent), m_student(student)
{
    QObject::connect(&PDM(), SIGNAL(courseDataChanged(std::string)),
                            this, SLOT(onCourseDataChanged(std::string)));
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


QAbstractItemModel* QCoursesListModel::getNextPageFromIndex(int index)
{
    if(m_student == nullptr)
    {
        return makeMainNavModel(elementAt<Course>(PDM().coursesBegin(), index));
    }
    else
    {
        return makeMainNavModel(elementAt<Course>(m_student->coursesBegin(), index));
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


QStringList QCoursesListModel::getOptionListForOperation(int operation)
{
    QStringList optionsList;

    switch(operation)
    {
        case AddExistingCourseToStudent:
        {
            assert(m_student != nullptr);
            std::vector<boost::shared_ptr<Course> > courses;
            std::set<boost::shared_ptr<Course> > allCourses(PDM().coursesBegin(), PDM().coursesEnd());
            std::set<boost::shared_ptr<Course> > studentCourses(m_student->coursesBegin(), m_student->coursesEnd());
            std::set_difference(allCourses.begin(), allCourses.end(), studentCourses.begin(), studentCourses.end(),
                                std::back_inserter(courses));
            std::sort(courses.begin(), courses.end());
            std::for_each(courses.begin(), courses.end(),
                          [&courses, &optionsList] (boost::shared_ptr<Course> course)
            {
                optionsList.push_back(QString::fromStdString(course->getCourseName()));
            });
        }
            break;

        default:
            // no other operation should have a list
            assert(false);
            break;
    }

    return optionsList;
}


void QCoursesListModel::addItem(QString courseName)
{
    assert(m_student == nullptr);
    boost::shared_ptr<Course> newCourse(new Course(courseName.toStdString()));

    unsigned int newRow = insertLocation(newCourse, PDM().coursesBegin(), PDM().coursesEnd());
    beginInsertRows(QModelIndex(), newRow, newRow);
    PDM().add(newCourse);
    endInsertRows();
}


void QCoursesListModel::removeItem(int row)
{
    beginRemoveRows(QModelIndex(), row, row);

    if(m_student == nullptr)
    {
        PDM().remove(iterAt<Course>(PDM().coursesBegin(), row));
    }
    else
    {
        m_student->removeCourse(iterAt<Course>(m_student->coursesBegin(), row));
    }

    endRemoveRows();
}


void QCoursesListModel::renameItem(QString newName, int row)
{
    assert(m_student == nullptr);
    boost::shared_ptr<Course> course = elementAt<Course>(PDM().coursesBegin(), row);
    course->updateCourseName(newName.toStdString());
    emit PDM().courseDataChanged(course->getUuid());
}


void QCoursesListModel::optionListSelection(int operation, int row)
{
    switch(operation)
    {
        case AddExistingCourseToStudent:
        {
            assert(m_student != nullptr);
            // perform the same actions that originally generated the courses list
            // so that we can determine the selected course
            std::vector<boost::shared_ptr<Course> > courses;
            std::set<boost::shared_ptr<Course> > allCourses(PDM().coursesBegin(), PDM().coursesEnd());
            std::set<boost::shared_ptr<Course> > studentCourses(m_student->coursesBegin(), m_student->coursesEnd());
            std::set_difference(allCourses.begin(), allCourses.end(), studentCourses.begin(), studentCourses.end(),
                                std::back_inserter(courses));
            std::sort(courses.begin(), courses.end());

            // now that we have the list, add the selected course to the student
            if(row < static_cast<int>(courses.size()))
            {
                unsigned int newRow = insertLocation(courses[row],
                                                     m_student->coursesBegin(),
                                                     m_student->coursesEnd());
                beginInsertRows(QModelIndex(), newRow, newRow);
                m_student->addCourse(courses[row]);
                endInsertRows();
            }
        }
            break;

        default:
            // no other operation should have a list
            assert(false);
            break;
    }
}


void QCoursesListModel::onCourseDataChanged(std::string uuid)
{
    auto coursesBegin = PDM().coursesBegin();
    auto coursesEnd = PDM().coursesEnd();

    if(m_student != nullptr)
    {
        coursesBegin = m_student->coursesBegin();
        coursesEnd = m_student->coursesEnd();
    }

    int i = 0;
    std::for_each(coursesBegin, coursesEnd,
                  [&uuid, &i, this] (boost::shared_ptr<Course> course)
    {
        if(course->getUuid() == uuid)
        {
            emit dataChanged(index(i), index(i));
        }
        ++i;
    });
}


QString QCoursesListModel::getOperationExplanationText(int operation, int row)
{
    switch(operation)
    {
        case AddCourse:
            return QString("Enter the name of the class to add:");

        case RemoveCourse:
            if(row < 0) return QString();
            return QString("Permanently remove the class \"" +
                           QString::fromStdString(elementAt<Course>(PDM().coursesBegin(), row)->getCourseName()) +
                           "\"?");

        case RenameCourse:
            if(row < 0) return QString();
            return QString("Permanently rename the class \"" +
                           QString::fromStdString(elementAt<Course>(PDM().coursesBegin(), row)->getCourseName()) +
                           "\" to:");

        case AddExistingCourseToStudent:
            assert(m_student != nullptr);
            return QString("Add " + QString::fromStdString(m_student->getDisplayName()) + " to the class:");

        case RemoveExistingCourseFromStudent:
            assert(m_student != nullptr);
            if(row < 0) return QString();
            return QString("Remove " + QString::fromStdString(m_student->getDisplayName()) + " from the class \"" +
                           QString::fromStdString(elementAt<Course>(m_student->coursesBegin(), row)->getCourseName()) +
                           "\"?");

        default:
            assert(false);
            break;
    }

    return QString();
}
