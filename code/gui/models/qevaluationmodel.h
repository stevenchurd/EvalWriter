#ifndef QEVALUATIONMODEL_H
#define QEVALUATIONMODEL_H

#include <QAbstractListModel>

#ifndef Q_MOC_RUN
#include <boost/shared_ptr.hpp>

#include "model/eval.h"
#endif

class QEvaluationModel : public QAbstractListModel
{
   Q_OBJECT

public:
    QEvaluationModel(boost::shared_ptr<Eval> eval, QObject* parent = 0) :
        QAbstractListModel(parent), m_eval(eval)
    {
    }

    virtual ~QEvaluationModel() {}

    /* virtual functions from QAbstractListModel */
    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role) const;

    Qt::ItemFlags flags(const QModelIndex &index) const;
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole);

    bool insertRows(int row, int count, const QModelIndex &parent);
    bool removeRows(int row, int count, const QModelIndex &parent);

private:
    boost::shared_ptr<Eval> m_eval;
};

#endif // QEVALUATIONMODEL_H
