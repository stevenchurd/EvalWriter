#include "qstudentslistmodel.h"
#include "utilities/persistentdatamanager.h"

QStudentsListModel::QStudentsListModel(QObject* parent) :
    QGenericListModel(parent)
{
}


QStudentsListModel::QStudentsListModel(boost::shared_ptr<Course> course, QObject* parent) :
    QGenericListModel(parent), m_course(course)
{
}


std::string QStudentsListModel::getItemString(int index) const
{
    boost::shared_ptr<Student> student;
    if(m_course == nullptr)
    {
        student = elementAt<Student>(PDM().studentsBegin(), index);
    }
    else
    {
        int i = 0;
        student = *std::find_if(PDM().studentsBegin(), PDM().studentsEnd(),
                     [&index, &i, this] (boost::shared_ptr<Student> vectStudent)->bool
        {
            if(vectStudent->isInCourse(m_course))
            {
                i++;
                return i-1 == index;
            }

            return false;
        });
    }

    return student->getFirstName() + " " + student->getMiddleName() + " " + student->getLastName();
}


int QStudentsListModel::getNumItems() const
{
    if(m_course == nullptr)
    {
        return std::distance(PDM().studentsBegin(), PDM().studentsEnd());
    }
    else
    {
        return std::count_if(PDM().studentsBegin(), PDM().studentsEnd(),
                             [this] (boost::shared_ptr<Student> student)
        {
            return student->isInCourse(m_course);
        });
    }
}


QAbstractItemModel* QStudentsListModel::getSubModelFromIndex(int index)
{
    if(m_course == nullptr)
    {
        return makeSubModel(elementAt<Student>(PDM().studentsBegin(), index));
    }
    else
    {
        int i = 0;
        boost::shared_ptr<Student> student = *std::find_if(PDM().studentsBegin(), PDM().studentsEnd(),
                     [&index, &i, this] (boost::shared_ptr<Student> vectStudent)->bool
        {
            if(vectStudent->isInCourse(m_course))
            {
                i++;
                return i-1 == index;
            }

            return false;
        });

        return makeSubModel(student);
    }
}


QList<int> QStudentsListModel::getSubModelOperations()
{
    QList<int> opList;

    return opList;
}


void QStudentsListModel::removeItem(int index)
{
    // TODO
}


void QStudentsListModel::renameItem(QString newName, int row)
{
    //TODO
}
