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
    QEvalSetsListModel(QVector<boost::shared_ptr<EvalSet> >& evalsets,
                       QObject* parent = 0);

    virtual ~QEvalSetsListModel() {}

private:
    QVector<boost::shared_ptr<EvalSet> >& m_evalsets;

    virtual std::string getItemString(int index) const;
    virtual int getNumItems() const;
};

#endif // QEVALSETSLISTMODEL_H
