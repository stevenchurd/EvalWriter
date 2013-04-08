#ifndef QEVALLISTMODEL_H
#define QEVALLISTMODEL_H

#include <QVector>
#include "qgenericlistmodel.h"

#ifndef Q_MOC_RUN
#include "model/eval.h"
#include "model/student.h"
#endif

class QEvalsListModel : public QGenericListModel
{
    Q_OBJECT
    Q_ENUMS(EvalsListOperations)

public:
    QEvalsListModel(boost::shared_ptr<Student> student, QObject* parent = 0);
    QEvalsListModel(boost::shared_ptr<EvalSet> evalSet, QObject* parent = 0);

    virtual ~QEvalsListModel() {}

    enum EvalsListOperations {
        AddEval = ModelOperationRanges::EvalsListOperationsBegin,
        AddExistingEvalToEvalSet,
        RemoveEval,
        RemoveEvalFromEvalSet,
        RenameEval,

        EndOfEnum
    };
    static_assert(EndOfEnum < ModelOperationRanges::EvalsListOperationsEnd,
                  "Too many items in enumeration");

public slots:
    virtual void addItem(QString newName);
    virtual void removeItem(int index);
    virtual void renameItem(QString newName, int row);
    virtual void optionListSelection(int operation, int row);

private:
    boost::shared_ptr<Student> m_student;
    boost::shared_ptr<EvalSet> m_evalSet;

    virtual QString getOperationExplanationText(int operation, int row);
    virtual QStringList getOptionListForOperation(int operation);
    virtual QAbstractItemModel* getSubModelFromIndex(int index);
    virtual QList<int> getSubModelOperations();
    virtual std::string getItemString(int index) const;
    virtual int getNumItems() const;
};


#endif // QEVALLISTMODEL_H
