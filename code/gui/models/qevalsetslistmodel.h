// (C) Copyright Steven Hurd 2013

#ifndef QEVALSETSLISTMODEL_H
#define QEVALSETSLISTMODEL_H

#include <QVector>
#include "qgenericlistmodel.h"
#include "globalenums.h"

#ifndef Q_MOC_RUN
#include "model/evalset.h"
#endif

class QEvalSetsListModel : public QGenericListModel
{
    Q_OBJECT
    Q_ENUMS(EvalSetsListOperations)

public:
    QEvalSetsListModel(QObject* parent = 0);
    QEvalSetsListModel(boost::shared_ptr<EvalSet> evalSet, QObject* parent = 0);

    virtual ~QEvalSetsListModel() {}

    enum EvalSetsListOperations {
        AddEvalSet = ModelOperationRanges::EvalSetsListOperationsBegin,
        RemoveEvalSet,
        RenameEvalSet,

        EndOfEnum
    };
    static_assert(EndOfEnum < ModelOperationRanges::EvalSetsListOperationsEnd,
                  "Too many items in enumeration");

    Q_INVOKABLE int getProgressIndicator(int row) const;

public slots:
    virtual void addItem(QString newName);
    virtual void removeItem(int index);
    virtual void renameItem(QString newName, int index);
    virtual void optionListSelection(int operation, int row);

private:
    boost::shared_ptr<EvalSet> m_evalSet;

    virtual QString getOperationExplanationText(int operation, int row);
    virtual QStringList getOptionListForOperation(int operation);
    virtual QAbstractItemModel* getNextPageFromIndex(int index);
    virtual QList<int> getSubModelOperations();
    virtual std::string getItemString(int index) const;
    virtual int getNumItems() const;
};

#endif // QEVALSETSLISTMODEL_H
