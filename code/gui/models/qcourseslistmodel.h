// (C) Copyright Steven Hurd 2013

#ifndef QCOURSESLISTMODEL_H
#define QCOURSESLISTMODEL_H

#include <QVector>
#include "qgenericlistmodel.h"

#ifndef Q_MOC_RUN
#include "model/course.h"
#endif

class QCoursesListModel : public QGenericListModel
{
public:
    QCoursesListModel(QVector<boost::shared_ptr<Course> >& courses,
                      QVector<boost::shared_ptr<Student> >& globalStudents,
                      QObject* parent = 0);

    virtual ~QCoursesListModel() {}

    virtual boost::shared_ptr<QMainNavigationModel> constructMainNavigationModel(int index) const;

private:
    QVector<boost::shared_ptr<Course> >& m_courses;
    QVector<boost::shared_ptr<Student> >& m_students;

    virtual std::string getItemString(int index) const;
    virtual int getNumItems() const;
};

#endif // QCOURSESLISTMODEL_H
