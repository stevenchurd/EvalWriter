// (C) Copyright Steven Hurd 2013

#include "qgradingcriteriamodel.h"
#include "model/criteriaitem.h"
#include "model/gradingcriteria.h"

QGradingCriteriaModel::QGradingCriteriaModel(
        QVector<boost::shared_ptr<GradingCriteria> > &gradingCriteria, QObject *parent) :
    QAbstractItemModel(parent), m_gradingCriteria(gradingCriteria)
{
}


Qt::ItemFlags QGradingCriteriaModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return 0;

    return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}


QModelIndex QGradingCriteriaModel::index(int row, int column, const QModelIndex &parent) const
{
    if (!hasIndex(row, column, parent))
    {
        return QModelIndex();
    }

    // if the element has a parent, it must be a criteria item
    if(parent.isValid())
    {
        return createIndex(row, column,
            m_gradingCriteria[parent.row()]->getCriteriaItem(row).get());
    }
    else
    {
        return createIndex(row, column);
    }
}


int QGradingCriteriaModel::rowCount(const QModelIndex &parent) const
{
    if(!parent.isValid())
    {
        return m_gradingCriteria.size();
    }
    if(parent.isValid() && parent.internalPointer() == 0)
    {
        return m_gradingCriteria[parent.row()]->getNumCriteriaItems();
    }

    return 0;
}


int QGradingCriteriaModel::columnCount(const QModelIndex &/*parent*/) const
{
    return 1;
}


QVariant QGradingCriteriaModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    switch(role)
    {
        case Qt::DisplayRole:
        {
            if(index.internalPointer() != 0)
            {
                CriteriaItem* ci = static_cast<CriteriaItem*>(index.internalPointer());
                return QString::fromStdString(ci->getItemStr());
            }
            else
            {
                return QString::fromStdString(m_gradingCriteria[index.row()]->getCriteriaName());
            }
            break;
        }

        default:
            return QVariant();
            break;
    }
}


QModelIndex QGradingCriteriaModel::parent(const QModelIndex &child) const
{
    if (!child.isValid())
        return QModelIndex();

    if(child.internalPointer() != 0)
    {
        CriteriaItem* ci = static_cast<CriteriaItem*>(child.internalPointer());
        for(int i = 0; i < m_gradingCriteria.size(); i++)
        {
            if(m_gradingCriteria[i]->getCriteriaName() == ci->getParentCriteriaName())
            {
                return createIndex(i, 0);
            }
        }
    }

    return QModelIndex();
}


QVariant QGradingCriteriaModel::headerData(int /*section*/, Qt::Orientation /*orientation*/, int /*role*/) const
{
    return QVariant();
}
