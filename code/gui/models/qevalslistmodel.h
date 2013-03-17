#ifndef QEVALLISTMODEL_H
#define QEVALLISTMODEL_H

#include <QVector>
#include "qgenericlistmodel.h"

#ifndef Q_MOC_RUN
#include "model/eval.h"
#endif

class QEvalsListModel : public QGenericListModel
{
    Q_OBJECT

public:
    QEvalsListModel(QVector<boost::shared_ptr<Eval> >& evals,
                    QObject* parent = 0);

    virtual ~QEvalsListModel() {}

private:
    QVector<boost::shared_ptr<Eval> >& m_evals;

    virtual std::string getItemString(int index) const;
    virtual int getNumItems() const;
};


#endif // QEVALLISTMODEL_H
