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
    QCoursesListModel(QObject* parent = 0);
    QCoursesListModel(boost::shared_ptr<Student> student, QObject* parent = 0);

    virtual ~QCoursesListModel() {}

private:
    boost::shared_ptr<Student> m_student;

    virtual std::string getItemString(int index) const;
    virtual int getNumItems() const;
};

#endif // QCOURSESLISTMODEL_H
