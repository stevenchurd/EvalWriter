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

class QGradingCriteriaModel : public QAbstractListModel
{
    Q_OBJECT

public:

    enum GradingCriteriaRoles {
        StringRole = Qt::UserRole + 1,
        NumCriteriaItemsRole,
        IsExpandedRole
    };

    QGradingCriteriaModel(QVector<boost::shared_ptr<GradingCriteria> >& gradingCriteria,
                          QVector<boost::shared_ptr<Student> >& students,
                          QObject* parent = 0);
    virtual ~QGradingCriteriaModel(void) {}

    Q_INVOKABLE QObject* criteriaItemModel(const int& index) const;

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
    QVector<boost::shared_ptr<GradingCriteria> >& m_gradingCriteria;
    QVector<boost::shared_ptr<Student> >& m_students;
    QVector<QCriteriaItemListModel*> m_criteriaItemListModels;
    QVector<bool> m_rowExpanded;
};

#endif // QGRADINGCRITERIAMODEL_H
