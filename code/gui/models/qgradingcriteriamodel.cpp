// (C) Copyright Steven Hurd 2013

#include "qgradingcriteriamodel.h"
#include "qcriteriaitemlistmodel.h"
#include "model/criteriaitem.h"
#include "model/gradingcriteria.h"

#include "utilities/persistentdatamanager.h"

QGradingCriteriaModel::QGradingCriteriaModel(QObject *parent) :
    QAbstractListModel(parent)
{
    int i = 0;
    std::for_each(PDM().gradingCriteriaBegin(),
                  PDM().gradingCriteriaEnd(),
                  [&i, this](const boost::shared_ptr<GradingCriteria>& gc)
    {
        auto newModel = std::make_tuple(new QCriteriaItemListModel(gc, i, this), false);

        m_criteriaItemListModels.push_back(newModel);

        connect(std::get<0>(newModel), SIGNAL(dataChanged(int)),
                this, SLOT(criteriaListDataChanged(int)));
        ++i;

    }
    );
}


QObject* QGradingCriteriaModel::getCriteriaItemModel(const int& index) const
{
    if(index > m_criteriaItemListModels.size() || index < 0)
        return nullptr;

    return static_cast<QObject*>(std::get<0>(m_criteriaItemListModels[index]));
}


Qt::ItemFlags QGradingCriteriaModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return 0;

    return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}


int QGradingCriteriaModel::rowCount(const QModelIndex &/*parent*/) const
{
    return std::distance(PDM().gradingCriteriaBegin(),
                         PDM().gradingCriteriaEnd());
}


QVariant QGradingCriteriaModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (index.row() > rowCount(QModelIndex()) || index.row() < 0)
        return QVariant();

    boost::shared_ptr<GradingCriteria> gc = *(std::next(PDM().gradingCriteriaBegin(), index.row()));

    switch(role)
    {
        case Qt::DisplayRole:
        case StringRole:
            return QString::fromStdString(gc->getCriteriaName());
            break;

        case NumCriteriaItemsRole:
            return QVariant::fromValue(gc->getNumCriteriaItems());
            break;

        case IsExpandedRole:
            return QVariant::fromValue(std::get<1>(m_criteriaItemListModels[index.row()]));
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
    std::get<1>(m_criteriaItemListModels[row]) = true;
    dataChanged(qmi, qmi);
}


void QGradingCriteriaModel::collapseRow(int row)
{
    QModelIndex qmi = index(row);
    std::get<1>(m_criteriaItemListModels[row]) = false;
    dataChanged(qmi, qmi);
}


// Generic function called in QML...in this case adds a grading criteria item
void QGradingCriteriaModel::addItem(QString itemName)
{
    boost::shared_ptr<GradingCriteria> newGc(new GradingCriteria(itemName.toStdString()));

    beginResetModel();
    // created grading criteria, now add it to PDM
    PDM().add(newGc);  // TODO: eventually this should return an index to where it was added

    // now add the model and connect the signal
    auto newModel = std::make_tuple(new QCriteriaItemListModel(newGc, m_criteriaItemListModels.size(), this), false);

    m_criteriaItemListModels.push_back(newModel);

    connect(std::get<0>(newModel), SIGNAL(dataChanged(int)),
            this, SLOT(criteriaListDataChanged(int)));
    endResetModel(); // TODO: add by index and use beginInsertRows
}


void QGradingCriteriaModel::removeGradingCriteria(int row)
{
    boost::shared_ptr<GradingCriteria> gc = elementAt<GradingCriteria>(PDM().gradingCriteriaBegin(), row);

    // prior to removing the grading criteria, remove
    // it's underlying criteria items.  This will gracefully
    // handle the replacement of criteria items in the underlying
    // evaluation data with custom text items
    while(gc->getNumCriteriaItems() != 0)
    {
        std::get<0>(m_criteriaItemListModels[row])->removeCriteriaItem(0);
    }

    beginRemoveRows(QModelIndex(), row, row);

    PDM().remove(iterAt<GradingCriteria>(PDM().gradingCriteriaBegin(), row));
    m_criteriaItemListModels.remove(row);

    int i = 0;
    std::for_each(m_criteriaItemListModels.begin(), m_criteriaItemListModels.end(),
                  [&i, this] (std::tuple<QCriteriaItemListModel*, bool> row)
    {
        std::get<0>(row)->updateParentIndex(i);
        ++i;
    });

    endRemoveRows();
}


void QGradingCriteriaModel::addCriteriaItem(int row, QString string, int level)
{
    std::get<0>(m_criteriaItemListModels[row])->addCriteriaItem(string, level);
    expandRow(row);
    emit dataChanged(index(row), index(row));
}


void QGradingCriteriaModel::modifyGradingCriteria(int row, QString string)
{
    boost::shared_ptr<GradingCriteria> gc = elementAt<GradingCriteria>(PDM().gradingCriteriaBegin(), row);

    gc->setCriteriaName(string.toStdString());
    emit dataChanged(index(row), index(row));
}


QList<int> QGradingCriteriaModel::getSubModelOperations()
{
    QList<int> opList;
    opList.push_back(AddGradingCriteria);
    return opList;
}


QString QGradingCriteriaModel::getOperationExplanationText(int operation, int /*row*/)
{
    QString explanationText;

    switch(operation)
    {
        case AddGradingCriteria:
            explanationText = QString("Enter the name of the Grading Category to add:");
            break;

        default:
            assert(false);
            break;
    }

    return explanationText;
}
