
#include "qgradingcriteriatreemodel.h"

QGradingCriteriaTreeModel::QGradingCriteriaTreeModel(QVector<boost::shared_ptr<GradingCriteria> > &gc,
                                                     QObject *parent) :
    m_gcItems(gc), QAbstractListModel(parent)
{
    foreach(boost::shared_ptr<GradingCriteria> item, gc)
    {
        boost::shared_ptr<GradingCriteriaTreeModelItem> newItem =
                boost::shared_ptr<GradingCriteriaTreeModelItem>(
                    new GradingCriteriaTreeModelItem(QString::fromStdString(item->getCriteriaName())));

        for(int i = 0; i < item->getNumCriteriaItems(); i++)
        {
            boost::shared_ptr<CriteriaItem> ci = item->getCriteriaItem(i);
            newItem->addChild(boost::shared_ptr<GradingCriteriaTreeModelItem>(
                                  new GradingCriteriaTreeModelItem(QString::fromStdString(ci->getItemStr()))));
        }

        m_listItems.append(newItem);
    }
}


QVariant QGradingCriteriaTreeModel::data(const QModelIndex &index, int role) const

{
    if (!index.isValid())
        return QVariant();

    if (index.row() > (m_listItems.size()-1) )
        return QVariant();

    boost::shared_ptr<GradingCriteriaTreeModelItem> item = m_listItems.at(index.row());

    switch (role)
    {
        case Qt::DisplayRole:
        case StringRole:
            return QVariant::fromValue(item->name);

        case LevelRole:
            return QVariant::fromValue(item->level);

        case IsOpenedRole:
            return QVariant::fromValue(item->isOpened);

        case HasChildrenRole:
            return QVariant::fromValue(item->hasChildren());

        default:
            return QVariant();
    }
}


int QGradingCriteriaTreeModel::rowCount(const QModelIndex &parent) const

{
    Q_UNUSED(parent)
    return m_listItems.size();
}


void QGradingCriteriaTreeModel::openItem(int numIndex)
{
    if (numIndex > (m_listItems.size()-1))
        return;

    if (m_listItems[numIndex]->isOpened)
        return;

    QModelIndex modelIndex = index(numIndex);

    m_listItems[numIndex]->isOpened = true;

    emit dataChanged(modelIndex, modelIndex);

    int i = numIndex+1;

    beginInsertRows(QModelIndex(), i, i+m_listItems[numIndex]->children.size()-1);

    foreach(boost::shared_ptr<GradingCriteriaTreeModelItem> item, m_listItems[numIndex]->children)
        m_listItems.insert(i++, item);

    endInsertRows();
}


void QGradingCriteriaTreeModel::closeItem(int numIndex)
{
    if (numIndex > (m_listItems.size()-1))
        return;

    if (!m_listItems[numIndex]->isOpened)
        return;

    QModelIndex modelIndex = index(numIndex);

    m_listItems[numIndex]->isOpened = false;

    emit dataChanged(modelIndex, modelIndex);

    int i = numIndex+1;

    for (; i < m_listItems.size() && (m_listItems[i]->level > m_listItems[numIndex]->level); ++i) {}

    --i;

    beginRemoveRows(QModelIndex(), numIndex+1, i);

    while (i > numIndex)
    {
        m_listItems[i]->isOpened = false;
        m_listItems.removeAt(i--);
    }

    endRemoveRows();
}


QHash<int, QByteArray> QGradingCriteriaTreeModel::roleNames() const
{
    static QHash<int, QByteArray> roleNames;

    if (roleNames.isEmpty())
    {
        roleNames[StringRole] = "string";
        roleNames[LevelRole] = "level";
        roleNames[IsOpenedRole] = "isOpened";
        roleNames[HasChildrenRole] = "hasChildren";
    }

    return roleNames;
}
