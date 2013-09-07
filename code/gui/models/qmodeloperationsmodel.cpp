#include "qmodeloperationsmodel.h"

QModelOperationsModel::QModelOperationsModel(QObject *parent) :
    QAbstractListModel(parent)
{
}


QHash<int,QByteArray> QModelOperationsModel::roleNames() const
{
    static QHash<int, QByteArray> roleNames;

    if (roleNames.isEmpty())
    {
        roleNames[OperationEnumRole] = "OperationEnum";
        roleNames[OperationExplanationRole] = "OperationExplanation";
        roleNames[OperationNameRole] = "OperationName";
        roleNames[OperationRequiresIndexRole] = "IndexRequired";
    }

    return roleNames;
}


QVariant QModelOperationsModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (index.row() >= static_cast<int>(m_modelOps.size()))
        return QVariant();

    const ModelOperation& modelOp = m_modelOps[index.row()];

    switch(role)
    {
        case Qt::DisplayRole:
        case OperationNameRole:
            return QVariant::fromValue(QString::fromStdString(modelOp.getOperationsName()));
            break;

        case OperationEnumRole:
            return QVariant::fromValue(QString::fromStdString(modelOp.getOperationEnum()));
            break;

        case OperationExplanationRole:
            return QVariant::fromValue(QString::fromStdString(modelOp.getOperationExplanation()));
            break;

        case OperationRequiresIndexRole:
            break;

        default:
            assert(false);
            return QVariant();
            break;
    }
}
