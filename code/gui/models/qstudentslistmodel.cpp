#include "qstudentslistmodel.h"
#include "utilities/persistentdatamanager.h"

QStudentsListModel::QStudentsListModel(QObject* parent) :
    QGenericListModel(parent)
{
}


boost::shared_ptr<QMainNavigationModel> QStudentsListModel::constructMainNavigationModel(int /*index*/) const
{
    //TODO: correct
    return boost::shared_ptr<QMainNavigationModel>(new QMainNavigationModel());
}


std::string QStudentsListModel::getItemString(int index) const
{
    auto student = elementAt<Student>(PDM().studentsBegin(), index);
    return student->getFirstName() + " " + student->getMiddleName() + " " + student->getLastName();
}


int QStudentsListModel::getNumItems() const
{
    return std::distance(PDM().studentsBegin(), PDM().studentsEnd());
}


boost::shared_ptr<Student> QStudentsListModel::getStudent(int index) const
{
    return elementAt<Student>(PDM().studentsBegin(), index);
}
