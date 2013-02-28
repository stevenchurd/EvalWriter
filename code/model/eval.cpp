// (C) Copyright Steven Hurd 2013

#include "eval.h"

#ifdef _DEBUG
#include <QDebug>
#endif

Eval::Eval(std::string evalName) :
    m_evalName(evalName)
{
}

void Eval::getPrintableEvalString(std::stringstream& ss)
{

    for(auto it = m_evalItems.begin();
        it != m_evalItems.end(); it++)
    {
        ss << (*it)->getItemStr();
    }
}


void Eval::addEvalItem(boost::shared_ptr<EvalItem> evalItem)
{
    m_evalItems.push_back(evalItem);
}


void Eval::removeEvalItemAt(int row)
{
    m_evalItems.erase(std::next(m_evalItems.begin(), row));
}


void Eval::moveEvalItem(int oldPosition, int newPosition)
{
    if(oldPosition+1 == newPosition || oldPosition-1 == newPosition)
    {
        std::iter_swap(std::next(m_evalItems.begin(), oldPosition),
                       std::next(m_evalItems.begin(), newPosition));
    }
    else if(oldPosition < newPosition)
    {
        // if the old position is to the left of the new position, rotate left
        std::rotate(std::next(m_evalItems.begin(), oldPosition),
                    std::next(m_evalItems.begin(), oldPosition+1),
                    std::next(m_evalItems.begin(), newPosition+1));
    }
    else if(oldPosition > newPosition)
    {
        // if it's to the right rotate right
        std::rotate(std::next(m_evalItems.rbegin(), m_evalItems.size()-oldPosition-1),
                    std::next(m_evalItems.rbegin(), m_evalItems.size()-oldPosition),
                    std::next(m_evalItems.rbegin(), m_evalItems.size()-newPosition));
    }
}


void Eval::replaceEvalItem(boost::shared_ptr<EvalItem> newItem, int oldId)
{
    std::replace_if(m_evalItems.begin(), m_evalItems.end(), hasId(oldId), newItem);
}


boost::shared_ptr<EvalItem> Eval::getEvalItem(unsigned int index) const
{
    if(index > m_evalItems.size())
    {
        throw ItemNotFoundException("Item not found: " + index);
    }

    return m_evalItems[index];
}


void Eval::acceptChildren(Visitor& visitor)
{
    BOOST_FOREACH(boost::shared_ptr<EvalItem> evalItem, m_evalItems)
    {
        evalItem->accept(visitor);
    }
}


#ifdef _DEBUG
    void Eval::printItems(void)
    {
        qDebug("____________________________");

        BOOST_FOREACH(boost::shared_ptr<EvalItem> evalItem, m_evalItems)
        {
            qDebug("%d: %s", evalItem->getUniqueId(), evalItem->getItemStr());
        }
        qDebug("____________________________");
    }
#endif
