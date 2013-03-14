#ifndef QGENERICLIST_H
#define QGENERICLIST_H

#include <QAbstractListModel>

#ifndef Q_MOC_RUN
#include <boost/shared_ptr.hpp>
#endif

class QGenericListModel : public QAbstractListModel
{
    Q_OBJECT

public:
    QGenericListModel(QObject* parent = 0);

    virtual ~QGenericListModel() {}

    enum EvaluationRoles{
        StringRole = Qt::UserRole + 1,
        ColorRole
    };

    /* virtual functions from QAbstractListModel */
    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;

    QHash<int,QByteArray> roleNames() const;

private:
    virtual std::string getItemString(int index) const = 0;
    virtual int getColorIndicator(int /*index*/) const { return -1; }
    virtual int getNumItems(void) const = 0;
};
#endif // QGENERICLIST_H
