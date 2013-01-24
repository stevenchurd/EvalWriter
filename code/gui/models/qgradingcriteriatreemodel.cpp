
#include "qgradingcriteriatreemodel.h"
#include "evalexceptions.h"


QGradingCriteriaTreeModel::QGradingCriteriaTreeModel(QVector<boost::shared_ptr<GradingCriteria> > &gc,
                                                     QObject *parent) :
    m_gcItems(gc), QAbstractListModel(parent)
{
    buildList();
}

void QGradingCriteriaTreeModel::buildList(void)
{
    foreach(boost::shared_ptr<GradingCriteria> item, m_gcItems)
    {
        boost::shared_ptr<GradingCriteriaTreeModelItem> newItem =
                boost::shared_ptr<GradingCriteriaTreeModelItem>(
                    new GradingCriteriaTreeModelItem(QString::fromStdString(item->getCriteriaName())));

        for(int i = 0; i < item->getNumCriteriaItems(); i++)
        {
            boost::shared_ptr<CriteriaItem> ci = item->getCriteriaItem(i);
            newItem->addChild(boost::shared_ptr<GradingCriteriaTreeModelItem>(
                                  new GradingCriteriaTreeModelItem(
                                      QString::fromStdString(ci->getItemStr()),
                                      ci->getCriteriaItemLevel())));
        }

        m_listItems.push_back(newItem);
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

        case IsGradingCriteriaRole:
            return QVariant::fromValue(item->isGradingCriteria());

        case HasChildrenRole:
            return QVariant::fromValue(item->hasChildren());

        case NumChildrenRole:
            return QVariant::fromValue(item->numChildren());

        case CriteriaLevelRole:
            return QVariant::fromValue(item->criteriaLevel);

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

    if (m_listItems[numIndex]->hasChildren() == false)
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
        roleNames[IsGradingCriteriaRole] = "isGradingCriteria";
        roleNames[HasChildrenRole] = "hasChildren";
        roleNames[NumChildrenRole] = "numChildren";
        roleNames[CriteriaLevelRole] = "criteriaLevel";
    }

    return roleNames;
}


void QGradingCriteriaTreeModel::removeGradingCriteria(int numIndex)
{
    if (numIndex > (m_listItems.size()-1))
        return;

    if(m_listItems[numIndex]->isGradingCriteria() != true)
        throw GenericModelException("Item was expected to be Grading criteria but was not: " + numIndex);

    int last = numIndex;

    if(m_listItems[numIndex]->isOpened)
    {
        // determine how many children need to be removed as well
        last += m_listItems[numIndex]->numChildren();
    }

    QModelIndex modelIndex = index(numIndex);

    emit dataChanged(modelIndex, modelIndex);

    beginRemoveRows(QModelIndex(), numIndex, last);

    ++last;
    while(numIndex != last)
    {
        m_listItems.removeAt(numIndex);
        --last;
    }

    endRemoveRows();

    //TODO
}


void QGradingCriteriaTreeModel::removeCriteriaItem(int numIndex)
{
    if (numIndex > (m_listItems.size()-1))
        return;

    if(m_listItems[numIndex]->isGradingCriteria() == true)
        throw GenericModelException("Item was not expected to be Grading criteria: " + numIndex);

    // first find the first parent before this item
    int parentIndex = -1;

    for(int i = numIndex-1; i >= 0 && parentIndex == -1; --i)
    {
        if(m_listItems[i]->isGradingCriteria())
        {
            parentIndex = i;
        }
    }

    if(parentIndex == -1)
    {
        throw ItemNotFoundException("Parent for current item not found: " + numIndex);
    }

    m_listItems[parentIndex]->removeChild(numIndex-parentIndex-1);

    QModelIndex parentModelIndex = index(parentIndex);
    QModelIndex modelIndex = index(numIndex);

    emit dataChanged(parentModelIndex, parentModelIndex);
    emit dataChanged(modelIndex, modelIndex);

    beginRemoveRows(QModelIndex(), numIndex, numIndex);
    m_listItems.removeAt(numIndex);
    endRemoveRows();


    //TODO
}


void QGradingCriteriaTreeModel::addGradingCriteria(QString name, QList<QMap<QString, int> > criteriaItems)
{
    //TODO
}


void QGradingCriteriaTreeModel::addCriteriaItem(QString name, int level)
{
    //TODO
}


void QGradingCriteriaTreeModel::modifyGradingCriteriaName(QString name)
{
    //TODO
}


void QGradingCriteriaTreeModel::modifyCriteriaItem(QString text, int level)
{
    //TODO
}
