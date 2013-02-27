// (C) Copyright Steven Hurd 2013

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

    enum EvaluationRoles{
        StringRole = Qt::UserRole + 1,
        LevelRole
    };

    /* virtual functions from QAbstractListModel */
    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;

    QHash<int,QByteArray> roleNames() const;

public slots:
    void move(int srcIndex, int destIndex);

private:
    boost::shared_ptr<Eval> m_eval;
};

#endif // QEVALUATIONMODEL_H
