// (C) Copyright Steven Hurd 2013

#include "eval.h"

Eval::Eval(std::string evalName) :
    m_evalName(evalName)
{
}

void Eval::getPrintableEvalString(std::stringstream& ss)
{

    for(std::vector<boost::shared_ptr<EvalItem> >::iterator it = m_evalItems.begin();
        it != m_evalItems.end(); it++)
    {
        ss << (*it)->getItemStr();
    }
}


void Eval::addEvalItem(boost::shared_ptr<EvalItem> evalItem)
{
    m_evalItems.push_back(evalItem);
}


void Eval::removeEvalItem(EvalItem::ItemUniqueIdType itemId)
{
    std::remove_if(m_evalItems.begin(), m_evalItems.end(), EvalItem::hasId(itemId));
}


void Eval::moveEvalItem(int oldPosition, int newPosition)
{
    // if the old position is to the left of the new position, rotate left
    if(oldPosition < newPosition)
    {
        std::rotate(std::next(m_evalItems.begin(), oldPosition),
                    std::next(m_evalItems.begin(),oldPosition+1),
                    std::next(m_evalItems.begin(), newPosition));
    }
    else if(oldPosition > newPosition)
    {
        // if it's to the right rotate right
        std::rotate(std::next(m_evalItems.rbegin(), m_evalItems.size()-oldPosition),
                    std::next(m_evalItems.rbegin(), m_evalItems.size()-oldPosition+1),
                    std::next(m_evalItems.rbegin(), m_evalItems.size()-newPosition));
    }
}


void Eval::replaceEvalItem(boost::shared_ptr<EvalItem> newItem, int oldId)
{
    std::replace_if(m_evalItems.begin(), m_evalItems.end(), EvalItem::hasId(oldId), newItem);
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
