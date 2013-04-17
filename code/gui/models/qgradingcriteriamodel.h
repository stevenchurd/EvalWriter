// (C) Copyright Steven Hurd 2013

#ifndef QGRADINGCRITERIAMODEL_H
#define QGRADINGCRITERIAMODEL_H

#include <QAbstractItemModel>
#include <QVector>

#include <tuple>

#include "globalenums.h"

#ifndef Q_MOC_RUN
#include <boost/shared_ptr.hpp>
#endif


class QCriteriaItemListModel;

class QGradingCriteriaModel : public QAbstractListModel
{
    Q_OBJECT
    Q_ENUMS(GradingCriteriaListOperations)

public:

    enum GradingCriteriaListOperations {
        AddGradingCriteria = ModelOperationRanges::GradingCriteriaListOperationsBegin,

        EndOfEnum
    };
    static_assert(EndOfEnum < ModelOperationRanges::GradingCriteriaListOperationsEnd,
                  "Too many items in enumeration");


    enum GradingCriteriaRoles {
        StringRole = Qt::UserRole + 1,
        NumCriteriaItemsRole,
        IsExpandedRole
    };

    QGradingCriteriaModel(QObject* parent = 0);
    virtual ~QGradingCriteriaModel(void) {}

    Q_INVOKABLE QObject* getCriteriaItemModel(const int& index) const;

    // operation interface
    Q_INVOKABLE QList<int> getSubModelOperations();
    Q_INVOKABLE QString getOperationExplanationText(int operation, int row);

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
    void addItem(QString itemName); // generic interface for adding grading criteria
    void removeGradingCriteria(int row);
    void addCriteriaItem(int row, QString string, int level);
    void modifyGradingCriteria(int row, QString string);

private:
    // tuple contains sub-list model and a boolean indicating if it is expanded
    QVector<std::tuple<QCriteriaItemListModel*, bool> > m_criteriaItemListModels;
};

#endif // QGRADINGCRITERIAMODEL_H
