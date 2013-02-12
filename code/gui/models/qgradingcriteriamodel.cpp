// (C) Copyright Steven Hurd 2013

#include "qgradingcriteriamodel.h"
#include "model/criteriaitem.h"
#include "model/gradingcriteria.h"

QGradingCriteriaModel::QGradingCriteriaModel(QVector<boost::shared_ptr<GradingCriteria> > &gradingCriteria,
                                             QVector<boost::shared_ptr<Student> > &students,
                                             QObject *parent) :
    QAbstractListModel(parent),
    m_gradingCriteria(gradingCriteria),
    m_students(students)
{
    int i = 0;
    foreach(boost::shared_ptr<GradingCriteria> gc, m_gradingCriteria)
    {
        m_criteriaItemListModels.push_back(new QCriteriaItemListModel(gc, students, i, this));
        m_rowExpanded.push_back(false);

        connect(m_criteriaItemListModels.back(), SIGNAL(dataChanged(int)),
                this, SLOT(criteriaListDataChanged(int)));
        ++i;
    }
}


Qt::ItemFlags QGradingCriteriaModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return 0;

    return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}


int QGradingCriteriaModel::rowCount(const QModelIndex &/*parent*/) const
{
    return m_gradingCriteria.size();
}


QVariant QGradingCriteriaModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (index.row() > m_gradingCriteria.size() || index.row() < 0)
        return QVariant();

    switch(role)
    {
        case Qt::DisplayRole:
        case StringRole:
            return QString::fromStdString(m_gradingCriteria[index.row()]->getCriteriaName());
            break;

        case NumCriteriaItemsRole:
            return QVariant::fromValue(m_gradingCriteria[index.row()]->getNumCriteriaItems());
            break;

        case IsExpandedRole:
            return QVariant::fromValue(m_rowExpanded[index.row()]);
            break;

        default:
            return QVariant();
            break;
    }
}


QHash<int,QByteArray> QGradingCriteriaModel::roleNames() const
{
    static QHash<int, QByteArray> roleNames;

    if (roleNames.isEmpty())
    {
        roleNames[StringRole] = "gradingCriteriaString";
        roleNames[NumCriteriaItemsRole] = "numCriteriaItems";
        roleNames[IsExpandedRole] = "isExpanded";
    }

    return roleNames;
}


void QGradingCriteriaModel::criteriaListDataChanged(int row)
{
    emit dataChanged(index(row), index(row));
}


void QGradingCriteriaModel::expandRow(int row)
{
    QModelIndex qmi = index(row);
    m_rowExpanded[row] = true;
    dataChanged(qmi, qmi);
}


void QGradingCriteriaModel::collapseRow(int row)
{
    QModelIndex qmi = index(row);
    m_rowExpanded[row] = false;
    dataChanged(qmi, qmi);
}


void QGradingCriteriaModel::removeGradingCriteria(int row)
{
    // prior to removing the grading criteria, remove
    // it's underlying criteria items.  This will gracefully
    // handle the replacement of criteria items in the underlying
    // evaluation data with custom text items
    while(m_gradingCriteria[row]->getNumCriteriaItems() != 0)
    {
        m_criteriaItemListModels[row]->removeCriteriaItem(0);
    }

    beginRemoveRows(QModelIndex(), row, row);
    m_gradingCriteria.remove(row);
    m_criteriaItemListModels.remove(row);
    m_rowExpanded.remove(row);
    endRemoveRows();
}


void QGradingCriteriaModel::addCriteriaItem(int row, QString string, int level)
{
    m_criteriaItemListModels[row]->addCriteriaItem(string, level);
    expandRow(row);
    emit dataChanged(index(row), index(row));
}
