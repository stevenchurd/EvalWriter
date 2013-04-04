#ifndef QGENERICLIST_H
#define QGENERICLIST_H

#include <QAbstractListModel>
#include <QStringList>

#include "qmainnavigationmodel.h"

#ifndef Q_MOC_RUN
#include <boost/shared_ptr.hpp>
#endif

class QGenericListModel : public QAbstractListModel
{
    Q_OBJECT

public:
    QGenericListModel(QObject* parent = 0);

    virtual ~QGenericListModel() {}

    enum GenericListRoles {
        StringRole = Qt::UserRole + 1,
        ColorRole,
        SubModelType,
        EndOfGenericListRoles
    };

    Q_INVOKABLE virtual QObject* getSubModelFromIndex(int index) = 0;
    Q_INVOKABLE virtual QList<int> getSubModelOperations() = 0;
    Q_INVOKABLE virtual QStringList getOptionListForOperation(int operation) = 0;
    Q_INVOKABLE virtual QString getOperationExplanationText(int operation, int row) = 0;

    /* virtual functions from QAbstractListModel */
    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;

    QHash<int,QByteArray> roleNames() const;

public slots:
    virtual void removeItem(int row) = 0;
    virtual void renameItem(QString newName, int row) = 0;
    virtual void optionListSelection(int operation, int row) = 0;

private:
    virtual std::string getItemString(int index) const = 0;
    virtual int getColorIndicator(int /*index*/) const { return -1; }
    virtual int getNumItems(void) const = 0;
};
#endif // QGENERICLIST_H
