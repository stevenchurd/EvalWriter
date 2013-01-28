// (C) Copyright Steven Hurd 2013

#ifndef QGRADINGCRITERIAMODEL_H
#define QGRADINGCRITERIAMODEL_H

#include <QAbstractItemModel>
#include <QVector>

#include "gui/models/qcriteriaitemlistmodel.h"

#ifndef Q_MOC_RUN
#include <boost/shared_ptr.hpp>

#include "model/gradingcriteria.h"
#endif

class QGradingCriteriaModel : public QAbstractItemModel
{
    Q_OBJECT

public:

    enum GradingCriteriaRoles {
        StringRole = Qt::UserRole + 1
    };

    QGradingCriteriaModel(QVector<boost::shared_ptr<GradingCriteria> >& gradingCriteria,
                          QObject* parent = 0);
    virtual ~QGradingCriteriaModel(void) {}

    Q_INVOKABLE QObject* criteriaItemModel(const int& index) const
    {
        return static_cast<QObject*>(m_criteriaItemListModels[index]);
    }

    /* functions inherited from QAbstractItemModel */
    Qt::ItemFlags flags(const QModelIndex &index) const;
    QModelIndex index(int row, int column, const QModelIndex &parent) const;
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QModelIndex parent(const QModelIndex &child) const;
    QHash<int,QByteArray> roleNames() const;

private:
    QVector<boost::shared_ptr<GradingCriteria> >& m_gradingCriteria;
    QVector<QCriteriaItemListModel*> m_criteriaItemListModels;
};

#endif // QGRADINGCRITERIAMODEL_H
