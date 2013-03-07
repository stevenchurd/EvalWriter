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
    QCriteriaItemListModel(boost::shared_ptr<GradingCriteria> gradingCriteria,
                           QVector<boost::shared_ptr<Student> >& students,
                           int parentIndex,
                           QObject* parent = 0);

    virtual ~QCriteriaItemListModel() {}

    enum CriteriaItemRoles {
        StringRole = Qt::UserRole + 1,
        LevelRole,
        UniqueIdRole
    };

    /* virtual functions from QAbstractListModel */
    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;

    QHash<int,QByteArray> roleNames() const;

    void updateParentIndex(const int index) { m_parentIndex = index; }

public slots:
    void addCriteriaItem(QString string, int level);
    void removeCriteriaItem(int row);
    void modifyCriteriaItem(int row, QString string, int level);

signals:
    void dataChanged(int parentIndex);

private:
    boost::shared_ptr<GradingCriteria> m_gradingCriteria;
    QVector<boost::shared_ptr<Student> >& m_students;
    int m_parentIndex;
};

#endif // QCRITERIAITEMMODEL_H
