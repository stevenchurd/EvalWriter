#ifndef QCRITERIAITEMLISTMODEL_H
#define QCRITERIAITEMLISTMODEL_H

#include <QAbstractListModel>

#ifndef Q_MOC_RUN
#include "boost/shared_ptr.hpp"
#include "model/gradingcriteria.h"
#endif

class QCriteriaItemListModel : public QAbstractListModel
{
    Q_OBJECT

public:
    QCriteriaItemListModel(boost::shared_ptr<GradingCriteria> gradingCriteria, int parentIndex,
                       QObject* parent = 0);

    virtual ~QCriteriaItemListModel() {}

    enum CriteriaItemRoles {
        StringRole = Qt::UserRole + 1,
        LevelRole
    };

    /* virtual functions from QAbstractListModel */
    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;

    QHash<int,QByteArray> roleNames() const;

public slots:
    void removeCriteriaItem(int row);

signals:
    void dataChanged(int parentIndex);

private:
    boost::shared_ptr<GradingCriteria> m_gradingCriteria;
    int m_parentIndex;
};

#endif // QCRITERIAITEMMODEL_H
