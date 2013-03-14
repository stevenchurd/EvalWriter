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
    Q_OBJECT

public:
    QCoursesListModel(QVector<boost::shared_ptr<Course> >& courses, QObject* parent = 0);

    virtual ~QCoursesListModel() {}

private:
    QVector<boost::shared_ptr<Course> >& m_courses;

    virtual std::string getItemString(int index) const;
    virtual int getNumItems() const;
};

#endif // QCOURSESLISTMODEL_H
