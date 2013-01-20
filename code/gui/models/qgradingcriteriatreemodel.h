#ifndef QGRADINGCRITERIATREEMODEL_H_
#define QGRADINGCRITERIATREEMODEL_H_

#include <QAbstractListModel>

#ifndef Q_MOC_RUN
#include <boost/shared_ptr.hpp>

#include "model/visitors/visitorelement.h"
#include "model/gradingcriteria.h"
#endif


class GradingCriteriaTreeModelItem
{
public:
    GradingCriteriaTreeModelItem(QString name_ = QString())
        : name(name_),
          level(0),
          isOpened(false)
    {}

    void adjustChildrenLevels()
    {
        foreach(boost::shared_ptr<GradingCriteriaTreeModelItem> item, children)
        {
            item->level = level+1;
            item->adjustChildrenLevels();
        }
    }

    void addChild(boost::shared_ptr<GradingCriteriaTreeModelItem> child)
    {
        children.append(child);
        adjustChildrenLevels();
    }

    QString name;
    int level;
    bool isOpened;
    QVector<boost::shared_ptr<GradingCriteriaTreeModelItem> > children;
    inline bool hasChildren() {return !children.empty();}
};


class QGradingCriteriaTreeModel : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit QGradingCriteriaTreeModel(QVector<boost::shared_ptr<GradingCriteria> >& gc, QObject *parent=0);

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QHash<int, QByteArray> roleNames() const;

public slots:
    void openItem(int numIndex);
    void closeItem(int numIndex);

private:
    Q_DISABLE_COPY(QGradingCriteriaTreeModel)

    QList<boost::shared_ptr<GradingCriteriaTreeModelItem> > m_listItems;
    QVector<boost::shared_ptr<GradingCriteria> >& m_gcItems;

    enum ListMenuItemRoles
    {
        StringRole = Qt::UserRole+1,
        LevelRole,
        IsOpenedRole,
        HasChildrenRole
    };
};

#endif
