#ifndef OBJECTPOOL_H
#define OBJECTPOOL_H

#include <list>
#include <boost/shared_ptr.hpp>
#include <boost/foreach.hpp>
#include "visitorelement.h"
#include "visitor.h"

template <typename T>
class ObjectPool : public VisitorElement
{
public:
    ObjectPool() {}
    virtual ~ObjectPool() {}

    void addItem(boost::shared_ptr<T> item);

    template <class OutputIterator>
        void getAll(OutputIterator dest);

    template <class OutputIterator, typename Predicate>
        void getAllMatching(OutputIterator dest, Predicate pred);

    void clear(void);

    /*
     * Visitor interface functions
     */
    void accept(Visitor& visitor) { visitor.visit<T>(*this); }

private:

    std::list<boost::shared_ptr<T> > m_pool;


};


template <typename T>
void ObjectPool<T>::addItem(boost::shared_ptr<T> newItem)
{
    m_pool.push_back(newItem);
}

template <typename T>
template <class OutputIterator, typename Predicate>
void ObjectPool<T>::getAllMatching(OutputIterator dest, Predicate pred)
{
    BOOST_FOREACH(boost::shared_ptr<T> item, m_pool)
    {
        if(pred(*item) == true)
        {
            dest++ = item;
        }
    }
}


template <typename T>
template <class OutputIterator>
void ObjectPool<T>::getAll(OutputIterator dest)
{
    BOOST_FOREACH(boost::shared_ptr<T> item, m_pool)
    {
        dest++ = item;
    }
}


template <typename T>
void ObjectPool<T>::clear(void)
{
    m_pool.clear();
}


#endif // OBJECTPOOL_H
