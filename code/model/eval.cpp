// (C) Copyright Steven Hurd 2013

#include "eval.h"

Eval::Eval(std::string evalName) :
    m_evalName(evalName)
{
}

void Eval::getPrintableEvalString(std::stringstream& ss)
{

    for(std::list<boost::shared_ptr<EvalItem> >::iterator it = m_evalItems.begin();
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
    for(std::list<boost::shared_ptr<EvalItem> >::iterator it = m_evalItems.begin();
        it != m_evalItems.end(); it++)
    {
        if((*it)->getUniqueId() == itemId)
        {
            it = m_evalItems.erase(it) ;
        }
    }
}


void Eval::acceptChildren(Visitor& visitor)
{
    BOOST_FOREACH(boost::shared_ptr<EvalItem> evalItem, m_evalItems)
    {
        evalItem->accept(visitor);
    }
}
