#ifndef QGRADINGCRITERIAMODEL_H
#define QGRADINGCRITERIAMODEL_H

#include <QAbstractItemModel>
#include <QVector>

#ifndef Q_MOC_RUN
#include <boost/shared_ptr.hpp>

#include "model/gradingcriteria.h"
#endif

class QGradingCriteriaModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    QGradingCriteriaModel(QVector<boost::shared_ptr<GradingCriteria> >& gradingCriteria,
                          QObject* parent = 0);
    virtual ~QGradingCriteriaModel(void) {}

    /* functions inherited from QAbstractItemModel */
    Qt::ItemFlags flags(const QModelIndex &index) const;
    QModelIndex index(int row, int column, const QModelIndex &parent) const;
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QModelIndex parent(const QModelIndex &child) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;

private:
    QVector<boost::shared_ptr<GradingCriteria> >& m_gradingCriteria;
};

#endif // QGRADINGCRITERIAMODEL_H
