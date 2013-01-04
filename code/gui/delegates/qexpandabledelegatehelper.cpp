// (C) Copyright Steven Hurd 2013

#include "qexpandabledelegatehelper.h"

#include <QHeaderView>

QExpandableDelegateHelper::QExpandableDelegateHelper(QTreeView *parent) :
    QObject(parent), m_viewPtr(parent)
{
    if (!m_viewPtr)
      return;

    m_viewPtr->setIndentation(10);
    m_viewPtr->setRootIsDecorated(false);
    m_viewPtr->header()->hide();
    connect(m_viewPtr, SIGNAL(clicked(QModelIndex)), this,
            SLOT(itemClicked(QModelIndex)));
}


void QExpandableDelegateHelper::itemClicked(const QModelIndex &index)
{
    if (!m_viewPtr)
        return;

    if (index.parent().isValid()) {
        if (index.model()->data(index,
                                SignalValueRole).isValid())
            emit itemClicked(index.model()->data(index,
                                                 SignalValueRole).toInt());
    } else {
        if (m_viewPtr->isExpanded(index))
            m_viewPtr->setExpanded(index, false);
        else {
            m_viewPtr->setExpanded(index, true);
            int childIndex = -1;
            while (index.child(childIndex+1, 0).isValid())
                childIndex++;

            if (childIndex != -1)
                m_viewPtr->scrollTo(index.child(childIndex, 0));
        }
    }
}
