#ifndef QGENERICLISTSORTFILTERPROXYMODEL_H
#define QGENERICLISTSORTFILTERPROXYMODEL_H

#include <QSortFilterProxyModel>
#include <QStringList>

class QGenericListSortFilterProxyModel : public QSortFilterProxyModel
{
        Q_OBJECT
    public:
        explicit QGenericListSortFilterProxyModel(QObject *parent = 0);

        // Q_INVOKABLE interface that GenericListModel exposes.  Need to forward
        // these calls with appropriate indices
        Q_INVOKABLE QObject* getNextPageFromIndex(int index) const;
        Q_INVOKABLE QList<int> getSubModelOperations() const;
        Q_INVOKABLE QStringList getOptionListForOperation(int operation) const;
        Q_INVOKABLE QString getOperationExplanationText(int operation, int row) const;

    signals:
        
    public slots:

        // slot interface that QGenericListModel exposes.  Need to forward
        // these slot calls with appropriate indices.
        void addItem(QString newName) const;
        void removeItem(int row) const;
        void renameItem(QString newName, int row) const;
        void optionListSelection(int operation, int row) const;

};

#endif // QGENERICLISTSORTFILTERPROXYMODEL_H
