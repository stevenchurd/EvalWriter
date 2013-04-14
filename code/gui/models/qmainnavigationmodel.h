#ifndef QMAINNAVIGATIONMODEL_H
#define QMAINNAVIGATIONMODEL_H

#include <QAbstractListModel>
#include <tuple>

#include "qgenericlistmodel.h"

#ifndef Q_MOC_RUN
#include <boost/shared_ptr.hpp>
#include "model/student.h"
#endif


class QMainNavigationModel : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit QMainNavigationModel(QString modelTitle, QObject *parent = 0);
    virtual ~QMainNavigationModel() {}

    enum MainNavModelRoles {
        StringRole = Qt::UserRole + 1,
        SubModelTypeRole
    };

    Q_INVOKABLE QObject* getSubModel(int index) const;
    Q_INVOKABLE int getSubModelType(int index) const;
    Q_INVOKABLE QString getModelTitle() const;
    Q_INVOKABLE unsigned int getSubModelCount(void) const { return static_cast<unsigned int>(m_submodels.size()); }

    void addSubModel(std::string displayString, QAbstractItemModel *listModel, QGenericListModel::SubModelType modelType);

    /* virtual functions from QAbstractListModel */
    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;

    QHash<int,QByteArray> roleNames() const;

private:

    QString m_modelTitle;
    std::vector<std::tuple<std::string, QAbstractItemModel*, QGenericListModel::SubModelType> > m_submodels;
};


QAbstractItemModel* makeSubModel(boost::shared_ptr<Student> student);
QAbstractItemModel* makeSubModel(boost::shared_ptr<Course> course);
QAbstractItemModel* makeSubModel(boost::shared_ptr<EvalSet> evalSet);


#endif // QMAINNAVIGATIONMODEL_H
