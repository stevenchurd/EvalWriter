#include "qstudentslistmodel.h"
#include "utilities/persistentdatamanager.h"
#include "qmainnavigationmodel.h"

QStudentsListModel::QStudentsListModel(QObject* parent) :
    QGenericListModel(parent)
{
    assert(QObject::connect(&PDM(), SIGNAL(studentDataChanged(std::string)),
                     this, SLOT(onStudentDataChanged(std::string))));
}


QStudentsListModel::QStudentsListModel(boost::shared_ptr<Course> course, QObject* parent) :
    QGenericListModel(parent), m_course(course)
{
    assert(QObject::connect(&PDM(), SIGNAL(studentDataChanged(std::string)),
                     this, SLOT(onStudentDataChanged(std::string))));
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
        student = getNthStudentInCourse(index, m_course);
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


QAbstractItemModel* QStudentsListModel::getNextPageFromIndex(int index)
{
    if(m_course == nullptr)
    {
        return makeMainNavModel(elementAt<Student>(PDM().studentsBegin(), index));
    }
    else
    {
        boost::shared_ptr<Student> student = getNthStudentInCourse(index, m_course);

        return makeMainNavModel(student);
    }
}


QList<int> QStudentsListModel::getSubModelOperations()
{
    QList<int> opList;

    if(m_course != nullptr)
    {
        opList.push_back(AddExistingStudentToCourse);
        opList.push_back(RemoveStudentFromCourse);
        opList.push_back(RenameStudent);
    }
    else
    {
        opList.push_back(AddStudent);
        opList.push_back(RemoveStudent);
        opList.push_back(RenameStudent);
    }

    return opList;
}


QStringList QStudentsListModel::getOptionListForOperation(int operation)
{
    QStringList optionsList;

    switch(operation)
    {
        case AddExistingStudentToCourse:
        {
            // get all students that aren't currently in this course
            assert(m_course != nullptr);
            std::vector<boost::shared_ptr<Student> > students;
            std::copy_if(PDM().studentsBegin(), PDM().studentsEnd(),
                         std::inserter(students, students.begin()),
                         [this] (boost::shared_ptr<Student> student)
                        { return !student->isInCourse(m_course); });
            std::sort(students.begin(), students.end());
            std::for_each(students.begin(), students.end(),
                          [&students, &optionsList] (boost::shared_ptr<Student> student)
            {
                optionsList.push_back(QString::fromStdString(student->getDisplayName()));
            });
        }
            break;

        default:
            assert(false);
            break;
    }

    return optionsList;
}


void QStudentsListModel::addStudent(QString firstName, QString middleName,
                                    QString lastName, int gender)
{
    boost::shared_ptr<Student> newStudent(
                new Student(firstName.toStdString(),
                            middleName.toStdString(),
                            lastName.toStdString(),
                            static_cast<Student::Gender>(gender)));

    beginResetModel();
    PDM().add(newStudent);
    endResetModel();
}


void QStudentsListModel::renameStudent(QString firstName, QString middleName, QString lastName, int row)
{
    boost::shared_ptr<Student> student;
    if(m_course != nullptr)
    {
        student = getNthStudentInCourse(row, m_course);
    }
    else
    {
        student = elementAt<Student>(PDM().studentsBegin(), row);
    }

    // TODO: eventually will want to update the ordering if this changes
    student->updateName(firstName.toStdString(), middleName.toStdString(),
                        lastName.toStdString());
    emit PDM().studentDataChanged(student->getUuid());
}



void QStudentsListModel::removeItem(int row)
{
    beginRemoveRows(QModelIndex(), row, row);
    if(m_course != nullptr)
    {
        // remove the student from the course by removing the course
        // from the selected student
        boost::shared_ptr<Student> student = getNthStudentInCourse(row, m_course);
        student->removeCourse(m_course->getUuid());
    }
    else
    {
        // this student is being removed permanently
        PDM().remove(iterAt<Student>(PDM().studentsBegin(), row));
    }
    endRemoveRows();
}


void QStudentsListModel::renameItem(QString /*newName*/, int /*row*/)
{
    assert(false); // this function should not be used for students
}


void QStudentsListModel::optionListSelection(int operation, int row)
{
    switch(operation)
    {
        case AddExistingStudentToCourse:
        {
            // get all students that aren't currently in this course
            assert(m_course != nullptr);
            std::vector<boost::shared_ptr<Student> > students;
            std::copy_if(PDM().studentsBegin(), PDM().studentsEnd(),
                         std::inserter(students, students.begin()),
                         [this] (boost::shared_ptr<Student> student)
                        { return !student->isInCourse(m_course); });
            std::sort(students.begin(), students.end());

            if(row < static_cast<int>(students.size()))
            {
                beginResetModel();
                students[row]->addCourse(m_course);
                endResetModel(); // TODO replace with beginInsertRow
            }
        }
            break;

        default:
            assert(false);
            break;
    }
}


void QStudentsListModel::onStudentDataChanged(std::string uuid)
{
    // see if this student exists in this view
    if(m_course == nullptr)
    {
        int i = 0;
        // this is the global list, student should exist
        std::for_each(PDM().studentsBegin(), PDM().studentsEnd(),
                      [&i, &uuid, this] (boost::shared_ptr<Student> student)
        {
            if(student->getUuid() == uuid)
            {
                emit dataChanged(index(i), index(i));
            }
            ++i;
        });
    }
    else
    {
        boost::shared_ptr<Student> student;
        int i = 0;

        student = getNthStudentInCourse(i, m_course);
        // otherwise get the nth student in the course until we've found a match or not
        while(student != nullptr)
        {
            if(student->getUuid() == uuid)
            {
                emit dataChanged(index(i), index(i));
            }
            ++i;
            student = getNthStudentInCourse(i, m_course);
        }
    }
}


QString QStudentsListModel::getOperationExplanationText(int operation, int row)
{
    QString explanationString;

    switch(operation)
    {
        case AddExistingStudentToCourse:
            assert(m_course != nullptr);
            explanationString = QString("Select student to add to " +
                                        QString::fromStdString(m_course->getCourseName()) + ":");
            break;

        case AddStudent:
            assert(m_course == nullptr);
            explanationString = QString("Enter the name of the student to add:");
            break;

        case RemoveStudentFromCourse:
        {
            assert(m_course != nullptr);
            if(row < 0) return QString();
            boost::shared_ptr<Student> student = getNthStudentInCourse(row, m_course);

            explanationString = QString("Remove " + QString::fromStdString(student->getDisplayName()) +
                                        " from the class " + QString::fromStdString(m_course->getCourseName()) +
                                        "?");
        }
            break;

        case RemoveStudent:
            assert(m_course == nullptr);
            if(row < 0) return QString();
            explanationString = QString("Permanently remove " +
                                        QString::fromStdString(elementAt<Student>(PDM().studentsBegin(), row)->getDisplayName()) +
                                        "?");
            break;

        case RenameStudent:
        {
            boost::shared_ptr<Student> student;
            if(m_course != nullptr)
            {
                student = getNthStudentInCourse(row, m_course);
            }
            else
            {
                student = elementAt<Student>(PDM().studentsBegin(), row);
            }
            explanationString = QString("Rename \"" +
                                        QString::fromStdString(student->getDisplayName()) + "\" to:");
        }
            break;

        default:
            assert(false);
            break;
    }

    return explanationString;
}
