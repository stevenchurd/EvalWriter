#ifndef QMAINNAVIGATIONMODEL_H
#define QMAINNAVIGATIONMODEL_H

#include <QAbstractListModel>
#include <tuple>

#ifndef Q_MOC_RUN
#include <boost/shared_ptr.hpp>
#include "model/student.h"
#endif

class QGenericListModel;

// we use these values in QML which is why we enumerate them explicitly
namespace ModelTypes {
enum SubModelType {
    StudentList = 1,
    EvaluationList = 2,
    CourseList = 3,
    EvalSetList = 4,
    GradingCriteria = 5
};
}

namespace ModelOperationRanges {
enum SubModelOperationRanges {
    InvalidOperation = 0,

    // CoursesList operations (1-10)
    CoursesListOperationsBegin = 1,
    CoursesListOperationsEnd = 10,

    // StudentsList operations (11-20)
    StudentsListOperationsBegin = 11,
    StudentsListOperationsEnd = 20,

    // EvalsList operations (21-30)
    EvalsListOperationsBegin = 21,
    EvalsListOperationsEnd = 30,

    // EvalSetsList operations (31-40)
    EvalSetsListOperationsBegin = 31,
    EvalSetsListOperationsEnd = 40,

    // Grading Griteria operations (41-50)
    GradingCriteriaListOperationsBegin = 41,
    GradingCriteriaListOperationsEnd = 50
};
}

class QMainNavigationModel : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit QMainNavigationModel(QString modelTitle, QObject *parent = 0);
    virtual ~QMainNavigationModel() {}

    enum MainNavModelRoles {
        StringRole = Qt::UserRole + 1,
        SubModelTypeRole
    };

    Q_INVOKABLE QObject* getSubModel(int index) const;
    Q_INVOKABLE int getSubModelType(int index) const;
    Q_INVOKABLE QString getModelTitle() const;
    Q_INVOKABLE int getSubModelCount(void) const { return m_submodels.size(); }

    void addSubModel(std::string displayString, QAbstractItemModel *listModel, ModelTypes::SubModelType modelType);

    /* virtual functions from QAbstractListModel */
    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;

    QHash<int,QByteArray> roleNames() const;

private:

    QString m_modelTitle;
    std::vector<std::tuple<std::string, QAbstractItemModel*, ModelTypes::SubModelType> > m_submodels;
};


QAbstractItemModel* makeSubModel(boost::shared_ptr<Student> student);
QAbstractItemModel* makeSubModel(boost::shared_ptr<Course> course);
QAbstractItemModel* makeSubModel(boost::shared_ptr<EvalSet> evalSet);


#endif // QMAINNAVIGATIONMODEL_H
