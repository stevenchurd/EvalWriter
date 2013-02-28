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
        LevelRole,
        SelectedRole,
        TitleRole,
        InPlaceEditable
    };

    /* virtual functions from QAbstractListModel */
    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;

    QHash<int,QByteArray> roleNames() const;

public slots:
    void move(int srcIndex, int destIndex);
    void removeItem(int row);
    void selectItem(int row);
    void deselectItem(int row);
    void deselectAllItems(void);

    void editItemString(int row, QString string);

private:
    boost::shared_ptr<Eval> m_eval;
    std::list<int> m_selected;
};

#endif // QEVALUATIONMODEL_H
