#ifndef QEXPANDABLEITEMDELEGATE_H
#define QEXPANDABLEITEMDELEGATE_H

#include <QAbstractItemDelegate>
#include <QStyledItemDelegate>
#include <QPointer>
#include <QTreeView>

class QExpandableItemDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    QExpandableItemDelegate(QTreeView *parent);
    void paint(QPainter *painter,
               const QStyleOptionViewItem &option,
               const QModelIndex &index) const;
    QSize sizeHint(const QStyleOptionViewItem &option,
                   const QModelIndex &index) const;

private:
    bool hasParent(const QModelIndex &index) const;
    bool isLast(const QModelIndex &index) const;

    bool isExpanded(const QModelIndex &index) const;
    QPointer<QTreeView> m_viewPtr;
};

#endif // QEXPANDABLEITEMDELEGATE_H
