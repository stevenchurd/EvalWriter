// (C) Copyright Steven Hurd 2013

#ifndef QEVALSETSLISTMODEL_H
#define QEVALSETSLISTMODEL_H

#include <QVector>
#include "qgenericlistmodel.h"

#ifndef Q_MOC_RUN
#include "model/evalset.h"
#endif

class QEvalSetsListModel : public QGenericListModel
{
    Q_OBJECT

public:
    QEvalSetsListModel(QObject* parent = 0);
    QEvalSetsListModel(boost::shared_ptr<EvalSet> evalSet, QObject* parent = 0);

    virtual ~QEvalSetsListModel() {}

private:
    boost::shared_ptr<EvalSet> m_evalSet;

    virtual QAbstractItemModel* getSubModelFromIndex(int index);
    virtual std::string getItemString(int index) const;
    virtual int getNumItems() const;
};

#endif // QEVALSETSLISTMODEL_H
