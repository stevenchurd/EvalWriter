#ifndef QSTUDENTLISTMODEL_H
#define QSTUDENTLISTMODEL_H

#include <QVector>
#include "qgenericlistmodel.h"

#ifndef Q_MOC_RUN
#include "model/student.h"
#endif

class QStudentsListModel : public QGenericListModel
{
    Q_OBJECT

public:
    QStudentsListModel(QObject* parent = 0);
    QStudentsListModel(boost::shared_ptr<Course> course, QObject* parent = 0);

    virtual ~QStudentsListModel() {}

private:
    boost::shared_ptr<Course> m_course;

    virtual std::string getItemString(int index) const;
    virtual int getNumItems() const;
};

#endif // QSTUDENTLISTMODEL_H
