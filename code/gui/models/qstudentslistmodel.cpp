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


QAbstractItemModel* QStudentsListModel::getSubModelFromIndex(int index)
{
    if(m_course == nullptr)
    {
        return makeSubModel(elementAt<Student>(PDM().studentsBegin(), index));
    }
    else
    {
        boost::shared_ptr<Student> student = getNthStudentInCourse(index, m_course);

        return makeSubModel(student);
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


void QStudentsListModel::addStudent(QString firstName, QString middleName, QString lastName)
{
    boost::shared_ptr<Student> newStudent(
                new Student(firstName.toStdString(), middleName.toStdString(), lastName.toStdString()));

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
    emit dataChanged(index(row), index(row));
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
