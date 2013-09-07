#ifndef QMODELOPERATIONSMODEL_H
#define QMODELOPERATIONSMODEL_H

#include <QAbstractListModel>
#include <vector>
#include "modeloperation.h"

class QModelOperationsModel : public QAbstractListModel
{
        Q_OBJECT
    public:
        explicit QModelOperationsModel(QObject *parent = 0);
        virtual ~QModelOperationsModel(void) {}

        enum ModelOperationsRoles {
            OperationEnumRole = Qt::UserRole + 1,
            OperationNameRole,
            OperationExplanationRole,
            OperationRequiresIndexRole
        };

        /* virtual functions from QAbstractListModel */
        QVariant data(const QModelIndex &index, int role) const;
        QHash<int,QByteArray> roleNames() const;

    private:
        std::vector<ModelOperation> m_modelOps;
        
};

#endif // QMODELOPERATIONSMODEL_H
