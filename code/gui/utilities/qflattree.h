#ifndef QFLATTREE_H
#define QFLATTREE_H

#include <QList>

#include "boost/shared_ptr.hpp"
#include "boost/any.hpp"

template <typename T>
class QFlatTreeNode
{
public:
    QFlatTreeNode(T& origTreeRef, bool isParentNode);

    template <typename InputIterator>
    void expandNode(InputIterator first);

    int numChildren(void)
    {
        return m_children.size();
    }

    void addChild(boost::any child)
    {
        m_children.push_back(child);
    }

private:
    T& m_originalTreeRef;
    bool m_isNodeExpanded;
    bool m_isParentNode;

    QList<boost::any> m_children;
};

template <typename T>
QFlatTreeNode<T>::QFlatTreeNode(T& origTreeRef, bool isParentNode) :
    m_originalTreeRef(origTreeRef), m_isNodeExpanded(false),
    m_isParentNode(isParentNode)
{
}


template <typename T>
template <typename InputIterator>
void QFlatTreeNode<T>::expandNode(InputIterator first)
{
    if(isNodeExpanded == false && isParentNode == true)
    {
        QList<T>::Iterator it = m_children.begin();
        while(it != m_children.end())
        {
            boost::shared_ptr<QFlatTreeNode> newFlatTreeNode(new QFlatTreeNode(*it));
            first++ = newFlatTreeNode;
            it++;
        }
    }
}


template <typename P, typename C>
class QFlatTree
{
public:
    QFlatTree(QVector<boost::shared_ptr<P> >& tree);

    void removeAt(int index);
    int getParentIndex(int index);
    int expandIndex(int index);
    int collapseIndex(int index);

private:

    QList<boost::any> m_flatlist;
    QVector<boost::shared_ptr<P> >& m_originalTree;

};

template <typename P, typename C>
QFlatTree<P, C>::QFlatTree(QVector<boost::shared_ptr<P> >& tree) :
    m_originalTree(tree), m_flatlist()
{
    QVector<boost::shared_ptr<P> >::Iterator it = tree.begin();

    while(it != tree.end())
    {
        boost::shared_ptr<P> parent = *it;

        // populate the tree
        m_flatlist.push_back(parent);

        c = parent->getChildIterator();
        m_flatlist.back().addChild(*c);

        ++it;
    }
}


#endif // QFLATTREE_H
