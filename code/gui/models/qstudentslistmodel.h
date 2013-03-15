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
    QStudentsListModel(QVector<boost::shared_ptr<Student> >& students, QObject* parent = 0);

    virtual ~QStudentsListModel() {}

    virtual boost::shared_ptr<QMainNavigationModel> constructMainNavigationModel(int index) const;

    boost::shared_ptr<Student> getStudent(int index) const;

private:
    QVector<boost::shared_ptr<Student> >& m_students;

    virtual std::string getItemString(int index) const;
    virtual int getNumItems() const;
};


boost::shared_ptr<QMainNavigationModel> constructMainNavigationModel(boost::shared_ptr<Student> student);

#endif // QSTUDENTLISTMODEL_H
