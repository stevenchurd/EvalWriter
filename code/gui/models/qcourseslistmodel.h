// (C) Copyright Steven Hurd 2013

#ifndef QCOURSESLISTMODEL_H
#define QCOURSESLISTMODEL_H

#include "qgenericlistmodel.h"
#include "globalenums.h"

#ifndef Q_MOC_RUN
#include "model/course.h"
#endif

class QCoursesListModel : public QGenericListModel
{
    Q_OBJECT
    Q_ENUMS(CoursesListOperations)

public:
    QCoursesListModel(QObject* parent = 0);
    QCoursesListModel(boost::shared_ptr<Student> student, QObject* parent = 0);

    virtual ~QCoursesListModel() {}

    enum CoursesListOperations {
        AddCourse = ModelOperationRanges::CoursesListOperationsBegin,
        RemoveCourse,
        RenameCourse,
        AddExistingCourseToStudent,
        RemoveExistingCourseFromStudent,

        EndOfEnum
    };
    static_assert(EndOfEnum < ModelOperationRanges::CoursesListOperationsEnd,
                  "Too many items in enumeration");

public slots:
    virtual void addItem(QString newName);
    virtual void removeItem(int row);
    virtual void renameItem(QString newName, int row);
    virtual void optionListSelection(int operation, int row);

private:
    boost::shared_ptr<Student> m_student;

    virtual QString getOperationExplanationText(int operation, int row);
    virtual QStringList getOptionListForOperation(int operation);
    virtual QAbstractItemModel* getNextPageFromIndex(int index);
    virtual QList<int> getSubModelOperations();
    virtual std::string getItemString(int index) const;
    virtual int getNumItems() const;
};

#endif // QCOURSESLISTMODEL_H
