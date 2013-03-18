// (C) Copyright Steven Hurd 2013

#include "qcourseslistmodel.h"
#include "qstudentsortfilterproxymodel.h"
#include "qstudentslistmodel.h"
#include "utilities/persistentdatamanager.h"

QCoursesListModel::QCoursesListModel(QObject* parent) :
    QGenericListModel(parent)
{
}


boost::shared_ptr<QMainNavigationModel> QCoursesListModel::constructMainNavigationModel(int /*index*/) const
{
    boost::shared_ptr<QMainNavigationModel> navModel(new QMainNavigationModel());

    return navModel;
}


std::string QCoursesListModel::getItemString(int index) const
{
    boost::shared_ptr<Course> course;
    course = *(std::next(PDM().coursesBegin(), index));
    return course->getCourseName();
}


int QCoursesListModel::getNumItems() const
{
    return std::distance(PDM().coursesBegin(),
                         PDM().coursesEnd());
}
