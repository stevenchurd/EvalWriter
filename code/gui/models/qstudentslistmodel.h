#ifndef QSTUDENTLISTMODEL_H
#define QSTUDENTLISTMODEL_H

#include <QVector>
#include "qgenericlistmodel.h"

#ifndef Q_MOC_RUN
#include "model/course.h"
#endif

class QStudentsListModel : public QGenericListModel
{
    Q_OBJECT

public:
    QStudentsListModel(QVector<boost::shared_ptr<Student> >& students, QObject* parent = 0);

    virtual ~QStudentsListModel() {}

private:
    QVector<boost::shared_ptr<Student> >& m_students;

    virtual std::string getItemString(int index) const;
    virtual int getNumItems() const;
};


#endif // QSTUDENTLISTMODEL_H
