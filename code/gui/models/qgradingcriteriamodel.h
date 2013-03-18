// (C) Copyright Steven Hurd 2013

#ifndef QGRADINGCRITERIAMODEL_H
#define QGRADINGCRITERIAMODEL_H

#include <QAbstractItemModel>
#include <QVector>

#include <tuple>

#include "gui/models/qcriteriaitemlistmodel.h"

#ifndef Q_MOC_RUN
#include <boost/shared_ptr.hpp>

#include "model/gradingcriteria.h"
#endif

class QGradingCriteriaModel : public QAbstractListModel
{
    Q_OBJECT

public:

    enum GradingCriteriaRoles {
        StringRole = Qt::UserRole + 1,
        NumCriteriaItemsRole,
        IsExpandedRole
    };

    QGradingCriteriaModel(QObject* parent = 0);
    virtual ~QGradingCriteriaModel(void) {}

    Q_INVOKABLE QObject* getCriteriaItemModel(const int& index) const;

    /* functions inherited from QAbstractItemModel */
    Qt::ItemFlags flags(const QModelIndex &index) const;
    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QHash<int,QByteArray> roleNames() const;

public slots:
    void criteriaListDataChanged(int row);

    void expandRow(int row);
    void collapseRow(int row);

    // actions that change model data
    void removeGradingCriteria(int row);
    void addCriteriaItem(int row, QString string, int level);
    void modifyGradingCriteria(int row, QString string);

private:
    // tuple contains sub-list model and a boolean indicating if it is expanded
    QVector<std::tuple<QCriteriaItemListModel*, bool> > m_criteriaItemListModels;
};

#endif // QGRADINGCRITERIAMODEL_H
