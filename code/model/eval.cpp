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
    std::remove_if(m_evalItems.begin(), m_evalItems.end(), EvalItem::hasId(itemId));
}


void Eval::replaceEvalItem(boost::shared_ptr<EvalItem> newItem, int oldId)
{
    std::replace_if(m_evalItems.begin(), m_evalItems.end(), EvalItem::hasId(oldId), newItem);
}


void Eval::acceptChildren(Visitor& visitor)
{
    BOOST_FOREACH(boost::shared_ptr<EvalItem> evalItem, m_evalItems)
    {
        evalItem->accept(visitor);
    }
}
