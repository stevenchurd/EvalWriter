#include "qcriteriaitemlistmodel.h"
#include "model/visitors/replacecriteriaitemvisitor.h"
#include "model/customtextitem.h"
#include "model/student.h"
#include "utilities/persistentdatamanager.h"

QCriteriaItemListModel::QCriteriaItemListModel(boost::shared_ptr<GradingCriteria> gradingCriteria,
        int parentIndex,
        QObject* parent) :
    QAbstractListModel(parent),
    m_gradingCriteria(gradingCriteria),
    m_parentIndex(parentIndex)
{
}

int QCriteriaItemListModel::rowCount(const QModelIndex &/*parent*/) const
{
    return m_gradingCriteria->getNumCriteriaItems();
}


QVariant QCriteriaItemListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (index.row() >= static_cast<int>(m_gradingCriteria->getNumCriteriaItems()))
        return QVariant();

    boost::shared_ptr<CriteriaItem> ci = m_gradingCriteria->getCriteriaItemAt(index.row());

    switch(role)
    {
        case Qt::DisplayRole:
        case StringRole:
            return QVariant::fromValue(
                        QString::fromStdString(ci->getItemStr()));
            break;

        case LevelRole:
            return QVariant::fromValue(static_cast<int>(ci->getCriteriaItemLevel()));
            break;

        case UniqueIdRole:
            return QVariant::fromValue(
                        QString::fromStdString(ci->getUuid()));
            break;

        default:
            return QVariant();
            break;
    }
}


QHash<int,QByteArray> QCriteriaItemListModel::roleNames() const
{
    static QHash<int, QByteArray> roleNames;

    if (roleNames.isEmpty())
    {
        roleNames[StringRole] = "criteriaString";
        roleNames[LevelRole] = "criteriaLevel";
        roleNames[UniqueIdRole] = "uniqueId";
   }

    return roleNames;
}


void QCriteriaItemListModel::addCriteriaItem(QString string, int level)
{
    boost::shared_ptr<CriteriaItem> ci(new CriteriaItem(m_gradingCriteria->getCriteriaName(),
                                                        string.toStdString(),
                                                        static_cast<CriteriaItem::CriteriaItemLevelType>(level)));
    unsigned int newRow = m_gradingCriteria->addCriteriaItem(ci);
    beginInsertRows(QModelIndex(), newRow, newRow);
    endInsertRows();
    emit dataChanged(m_parentIndex);
}


void QCriteriaItemListModel::removeCriteriaItem(int row)
{
    beginRemoveRows(QModelIndex(), row, row);

    boost::shared_ptr<EvalItem> oldItem = m_gradingCriteria->getCriteriaItemAt(row);
    boost::shared_ptr<EvalItem> newCustomTextItem = boost::shared_ptr<EvalItem>(
                new CustomTextItem(oldItem->getItemTitleStr(), oldItem->getItemStr()));

    // first remove from the item
    m_gradingCriteria->removeCriteriaItemAt(row);

    //now transform the removed criteria item to a custom text item in any evals it might
    //have existed in
    ReplaceCriteriaItemVisitor rciv(newCustomTextItem, oldItem->getUuid());

    std::for_each(PDM().studentsBegin(), PDM().studentsEnd(),
                  [&rciv] (boost::shared_ptr<Student> student)
    {
        student->accept(rciv);
    });

    endRemoveRows();

    emit dataChanged(m_parentIndex);
}


void QCriteriaItemListModel::modifyCriteriaItem(int row, QString string, int level)
{
    beginResetModel();
    m_gradingCriteria->getCriteriaItemAt(row)->setItemStr(string.toStdString());
    m_gradingCriteria->getCriteriaItemAt(row)->setCriteriaItemLevelValue(
                static_cast<CriteriaItem::CriteriaItemLevelType>(level));
    endResetModel();
}
