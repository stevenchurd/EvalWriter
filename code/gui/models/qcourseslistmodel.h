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

    virtual ~QCoursesListModel() {}

    virtual boost::shared_ptr<QMainNavigationModel> constructMainNavigationModel(int index) const;

private:
    virtual std::string getItemString(int index) const;
    virtual int getNumItems() const;
};

#endif // QCOURSESLISTMODEL_H
