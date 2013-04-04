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

public slots:
    virtual void removeItem(int index);
    virtual void renameItem(QString newName, int row);
    virtual void optionListSelection(int operation, int row);

private:
    boost::shared_ptr<Course> m_course;

    virtual QStringList getOptionListForOperation(int operation);
    virtual QAbstractItemModel* getSubModelFromIndex(int index);
    virtual QList<int> getSubModelOperations();
    virtual std::string getItemString(int index) const;
    virtual int getNumItems() const;
};

#endif // QSTUDENTLISTMODEL_H
