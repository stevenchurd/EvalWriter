#ifndef QGRADINGCRITERIATREEMODEL_H_
#define QGRADINGCRITERIATREEMODEL_H_

#include <QAbstractListModel>

#ifndef Q_MOC_RUN
#include <boost/shared_ptr.hpp>

#include "model/visitors/visitorelement.h"
#include "model/gradingcriteria.h"
#include "gui/utilities/qflattree.h"
#endif


class GradingCriteriaTreeModelItem
{
public:
    GradingCriteriaTreeModelItem(QString name_ = QString(), int criteriaLevel_ = 0)
        : name(name_),
          criteriaLevel(criteriaLevel_),
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
        children.push_back(child);
        adjustChildrenLevels();
    }

    void removeChild(int index)
    {
        children.remove(index);
    }

    QString name;
    int level;
    bool isOpened;
    int criteriaLevel;
    QVector<boost::shared_ptr<GradingCriteriaTreeModelItem> > children;

    inline bool hasChildren() {return !children.empty();}
    inline int numChildren() { return children.size(); }
    inline bool isGradingCriteria() { return level == 0; }
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
    void removeGradingCriteria(int numIndex);
    void removeCriteriaItem(int numIndex);
    void addGradingCriteria(QString name, QList<QMap<QString, int> > criteriaItems);
    void addCriteriaItem(QString name, int level);
    void modifyGradingCriteriaName(QString name);
    void modifyCriteriaItem(QString text, int level);

private:
    Q_DISABLE_COPY(QGradingCriteriaTreeModel)

    void buildList(void);

    QList<boost::shared_ptr<GradingCriteriaTreeModelItem> > m_listItems;
    QVector<boost::shared_ptr<GradingCriteria> >& m_gcItems;

    enum ListMenuItemRoles
    {
        StringRole = Qt::UserRole+1,
        LevelRole,
        IsOpenedRole,
        IsGradingCriteriaRole,
        HasChildrenRole,
        NumChildrenRole,
        CriteriaLevelRole
    };
};

#endif
