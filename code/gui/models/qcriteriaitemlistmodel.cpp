#include "qcriteriaitemlistmodel.h"
#include "model/visitors/replacecriteriaitemvisitor.h"
#include "model/customtextitem.h"
#include "model/student.h"

QCriteriaItemListModel::QCriteriaItemListModel(
        boost::shared_ptr<GradingCriteria> gradingCriteria,
        QVector<boost::shared_ptr<Student> >& students,
        int parentIndex,
        QObject* parent) :
    QAbstractListModel(parent),
    m_gradingCriteria(gradingCriteria),
    m_students(students),
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

    if (index.row() >= m_gradingCriteria->getNumCriteriaItems())
        return QVariant();

    boost::shared_ptr<CriteriaItem> ci = m_gradingCriteria->getCriteriaItem(index.row());

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
   }

    return roleNames;
}


void QCriteriaItemListModel::addCriteriaItem(QString string, int level)
{
    beginResetModel();
    m_gradingCriteria->addCriteriaItem(string.toStdString(), static_cast<CriteriaItem::CriteriaItemLevelType>(level));
    endResetModel();
}


void QCriteriaItemListModel::removeCriteriaItem(int row)
{
    beginRemoveRows(QModelIndex(), row, row);

    boost::shared_ptr<EvalItem> oldItem = m_gradingCriteria->getCriteriaItem(row);
    boost::shared_ptr<EvalItem> newCustomTextItem = boost::shared_ptr<EvalItem>(new CustomTextItem(oldItem->getItemStr()));

    // first remove from the item
    m_gradingCriteria->removeCriteriaItemAt(row);

    //now transform the removed criteria item to a custom text item in any evals it might
    //have existed in
    ReplaceCriteriaItemVisitor rciv(newCustomTextItem, oldItem->getUniqueId());

    BOOST_FOREACH(boost::shared_ptr<Student> student, m_students)
    {
        student->accept(rciv);
    }

    endRemoveRows();

    emit dataChanged(m_parentIndex);
}


void QCriteriaItemListModel::modifyCriteriaItem(int row, QString string, int level)
{
    beginResetModel();
    m_gradingCriteria->getCriteriaItem(row)->setItemStr(string.toStdString());
    m_gradingCriteria->getCriteriaItem(row)->setCriteriaItemLevelValue(
                static_cast<CriteriaItem::CriteriaItemLevelType>(level));
    endResetModel();
}
