#include <QPainter>

#include "qexpandableitemdelegate.h"

#include "gui/delegates/qexpandabledelegatehelper.h"

QExpandableItemDelegate::QExpandableItemDelegate(QTreeView *parent) :
    QStyledItemDelegate(parent), m_viewPtr(parent)
{
}


bool QExpandableItemDelegate::hasParent(const QModelIndex &index) const
{
    if (index.parent().isValid())
        return true;

    return false;
}


bool QExpandableItemDelegate::isLast(const QModelIndex &index) const
{
    if (index.parent().isValid()) {
        if (!index.parent().child(index.row()+1,
                                  index.column()).isValid()) {
            return true;
        }
    }

    return false;
}

bool QExpandableItemDelegate::isExpanded(const QModelIndex &index) const
{
    if (!m_viewPtr)
        return false;

    return m_viewPtr->isExpanded(index);
}


QSize QExpandableItemDelegate::sizeHint(
        const QStyleOptionViewItem &option,
        const QModelIndex &index) const
{
    if (index.model()->data(index, QExpandableDelegateHelper::TypeRole)
            == QExpandableDelegateHelper::Spacer)
    {
        return QSize(option.rect.width(), 10);
    }
    else
    {
        return QSize(option.rect.width(), 30);
    }
}


void QExpandableItemDelegate::paint(QPainter *painter,
                           const QStyleOptionViewItem &option,
                           const QModelIndex &index) const
{
    if (!m_viewPtr)
        return;

    if (index.model()->data(index, QExpandableDelegateHelper::TypeRole)
            == QExpandableDelegateHelper::Spacer ) {
        // No need to draw spacer items
        return;
    }

    if (option.state & QStyle::State_Selected)
    {
        //painter->fillRect(option.rect, option.palette.highlight());
        //painter->setPen(option.palette.highlightedText().color());
    }

    // Setup pens and colors

    if (!hasParent(index)) {
        // Paint the top-item
        painter->save();
        painter->setPen(QColor(Qt::blue));
        painter->drawRoundedRect(option.rect, 10, 10);
        painter->restore();
        //painter->fillRect(option.rect,Qt::SolidPattern);
        if (isExpanded(index)) {
            // Expanded
        } else {
            // Closed
        }
    } else if (isLast(index)) {
        // Paint the bottom item
    } else {
        // Paint middle items
    }

    // Draw common parts here (decoration and text)
    painter->drawText(option.rect, Qt::AlignLeft | Qt::AlignVCenter, index.data(Qt::DisplayRole).toString());

}
