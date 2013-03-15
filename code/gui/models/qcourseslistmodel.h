// (C) Copyright Steven Hurd 2013

#ifndef QCOURSESLISTMODEL_H
#define QCOURSESLISTMODEL_H

#include <QVector>
#include "qgenericlistmodel.h"

#ifndef Q_MOC_RUN
#include "model/course.h"
#endif

namespace MainNavigationModelCreationRoutines {
template <typename Pred1, typename Pred2>
boost::shared_ptr<QMainNavigationModel> constructMainNavigationModel(
        boost::shared_ptr<Course> course, Pred1 studentsBegin, Pred2 studentsEnd);
}

template <typename Pred1, typename Pred2>
class QCoursesListModel : public QGenericListModel
{
public:
    QCoursesListModel(QVector<boost::shared_ptr<Course> >& courses,
                      Pred1 studentsBegin, Pred2 studentsEnd,
                      QObject* parent = 0);

    virtual ~QCoursesListModel() {}

    virtual boost::shared_ptr<QMainNavigationModel> constructMainNavigationModel(int index) const;

private:
    QVector<boost::shared_ptr<Course> >& m_courses;
    Pred1 m_studentsBegin;
    Pred2 m_studentsEnd;

    virtual std::string getItemString(int index) const;
    virtual int getNumItems() const;
};


template <typename Pred1, typename Pred2>
QCoursesListModel<Pred1, Pred2>::QCoursesListModel(QVector<boost::shared_ptr<Course> >& courses,
                                     Pred1 studentsBegin,
                                     Pred2 studentsEnd,
                                     QObject* parent) :
    QGenericListModel(parent), m_courses(courses), m_studentsBegin(studentsBegin), m_studentsEnd(studentsEnd)
{
}


template <typename Pred1, typename Pred2>
boost::shared_ptr<QMainNavigationModel> QCoursesListModel<Pred1, Pred2>::constructMainNavigationModel(int index) const
{
    return MainNavigationModelCreationRoutines::constructMainNavigationModel(m_courses[index], m_studentsBegin, m_studentsEnd);
}


template <typename Pred1, typename Pred2>
std::string QCoursesListModel<Pred1, Pred2>::getItemString(int index) const
{
    return m_courses[index]->getCourseName();
}


template <typename Pred1, typename Pred2>
int QCoursesListModel<Pred1, Pred2>::getNumItems() const
{
    return m_courses.size();
}


namespace MainNavigationModelCreationRoutines {

template <typename Pred1, typename Pred2>
boost::shared_ptr<QMainNavigationModel> constructMainNavigationModel(
        boost::shared_ptr<Course> course, Pred1 studentsBegin, Pred2 studentsEnd)
{
    std::vector<boost::shared_ptr<Student> > students;

    std::for_each(studentsBegin(), studentsEnd(),
                  [&students, &course] (boost::shared_ptr<Student> student) {
                      if(student->isInCourse(course) == true) { students.push_back(student); }
                   });

    boost::shared_ptr<QMainNavigationModel> navModel(new QMainNavigationModel());

    return navModel;
}

} //end namespace

#endif // QCOURSESLISTMODEL_H
