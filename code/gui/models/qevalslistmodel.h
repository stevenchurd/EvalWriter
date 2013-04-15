#ifndef QEVALLISTMODEL_H
#define QEVALLISTMODEL_H

#include <QVector>
#include "qgenericlistmodel.h"
#include "globalenums.h"

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

    enum GenericListRoles {
        StringRole = Qt::UserRole + 1,
        ProgressRole
    };

    /* virtual functions from QAbstractListModel */
    QVariant data(const QModelIndex &index, int role) const;
    QHash<int,QByteArray> roleNames() const;

public slots:
    virtual void addItem(QString newName);
    virtual void removeItem(int index);
    virtual void renameItem(QString newName, int row);
    virtual void optionListSelection(int operation, int row);

    void onEvalDataChanged(std::string uuid);

private:
    boost::shared_ptr<Student> m_student;
    boost::shared_ptr<EvalSet> m_evalSet;

    virtual QString getOperationExplanationText(int operation, int row);
    virtual QStringList getOptionListForOperation(int operation);
    virtual QAbstractItemModel* getNextPageFromIndex(int index);
    virtual QList<int> getSubModelOperations();
    virtual std::string getItemString(int index) const;
    virtual int getNumItems() const;

    int getProgressIndicator(int row) const;
};


#endif // QEVALLISTMODEL_H
