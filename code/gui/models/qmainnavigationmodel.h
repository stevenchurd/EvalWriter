#ifndef QMAINNAVIGATIONMODEL_H
#define QMAINNAVIGATIONMODEL_H

#include <QAbstractListModel>
#include <tuple>

class QGenericListModel;

class QMainNavigationModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit QMainNavigationModel(QObject *parent = 0);

    enum MainNavModelRoles {
        StringRole = Qt::UserRole + 1
    };

    Q_INVOKABLE QObject* getSubModel(int index) const;
    void addSubModel(std::string displayString, QAbstractItemModel *listModel);

    /* virtual functions from QAbstractListModel */
    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;

    QHash<int,QByteArray> roleNames() const;

private:

    std::vector<std::tuple<std::string, QAbstractItemModel*> > m_submodels;
};

#endif // QMAINNAVIGATIONMODEL_H
