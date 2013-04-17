#ifndef QSTUDENTLISTMODEL_H
#define QSTUDENTLISTMODEL_H

#include <QVector>
#include "qgenericlistmodel.h"
#include "globalenums.h"

class Course;

class QStudentsListModel : public QGenericListModel
{
    Q_OBJECT
    Q_ENUMS(StudentsListOperations)

public:
    QStudentsListModel(QObject* parent = 0);
    QStudentsListModel(boost::shared_ptr<Course> course, QObject* parent = 0);

    virtual ~QStudentsListModel() {}

    enum StudentsListOperations {
        AddStudent = ModelOperationRanges::StudentsListOperationsBegin,
        RemoveStudent,
        RenameStudent,
        AddExistingStudentToCourse,
        RemoveStudentFromCourse,

        EndOfEnum
    };
    static_assert(EndOfEnum < ModelOperationRanges::StudentsListOperationsEnd,
                  "Too many items in enumeration");

public slots:
    void addStudent(QString firstName, QString middleName, QString lastName, int gender);
    void renameStudent(QString firstName, QString middleName, QString lastName, int row);
    virtual void removeItem(int index);
    virtual void renameItem(QString newName, int row);
    virtual void optionListSelection(int operation, int row);

    void onStudentDataChanged(std::string uuid);

private:
    boost::shared_ptr<Course> m_course;

    virtual QString getOperationExplanationText(int operation, int row);
    virtual QStringList getOptionListForOperation(int operation);
    virtual QAbstractItemModel* getNextPageFromIndex(int index);
    virtual QList<int> getSubModelOperations();
    virtual std::string getItemString(int index) const;
    virtual int getNumItems() const;
};

#endif // QSTUDENTLISTMODEL_H
