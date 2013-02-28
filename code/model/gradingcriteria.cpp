// (C) Copyright Steven Hurd 2013

#include <algorithm>
#include <sstream>
#include "gradingcriteria.h"
#include "criteriaitem.h"

GradingCriteria::GradingCriteria(std::string criteriaName) :
    m_criteriaName(criteriaName)
{
}

EvalItem::ItemUniqueIdType GradingCriteria::addCriteriaItem(std::string descStr, CriteriaItem::CriteriaItemLevelType level)
{
    boost::shared_ptr<CriteriaItem> ci(new CriteriaItem(m_criteriaName, descStr, level));
    m_criteriaItems.push_back(ci);

    return m_criteriaItems.back()->getUniqueId();
}


void GradingCriteria::removeCriteriaItem(EvalItem::ItemUniqueIdType id)
{
    std::remove_if(m_criteriaItems.begin(),
                   m_criteriaItems.end(),
                   hasId(id)) ;
}


void GradingCriteria::removeCriteriaItemAt(unsigned int pos)
{
    if(pos > m_criteriaItems.size())
        throw ItemNotFoundException("Invalid item for removal: " + pos);

    m_criteriaItems.erase(m_criteriaItems.begin() + pos);
}


int GradingCriteria::getNumCriteriaItems(void) const
{
    return m_criteriaItems.size();
}


boost::shared_ptr<CriteriaItem> GradingCriteria::getCriteriaItem(
        std::string criteriaName,
        CriteriaItem::CriteriaItemLevelType level)
{
    std::vector<boost::shared_ptr<CriteriaItem> >::iterator it ;

    it = std::find_if(m_criteriaItems.begin(),
                      m_criteriaItems.end(),
                      findCriteriaItem(criteriaName, m_criteriaName, level));

    if(it == m_criteriaItems.end())
    {
        std::ostringstream levelNum;
        levelNum << level;

        throw ItemNotFoundException("Item not found: " + criteriaName + " with level " + levelNum.str());
    }

    return *it;
}


boost::shared_ptr<CriteriaItem> GradingCriteria::getCriteriaItem(unsigned int index) const
{
    if(index > m_criteriaItems.size())
    {
        throw ItemNotFoundException("Item not found: " + index);
    }

    return m_criteriaItems[index];
}


void GradingCriteria::updateCriteriaItem(EvalItem::ItemUniqueIdType id, std::string itemStr)
{
    std::vector<boost::shared_ptr<CriteriaItem> >::iterator it ;

    it = std::find_if(m_criteriaItems.begin(), m_criteriaItems.end(), hasId(id)) ;

    if(it == m_criteriaItems.end())
    {
        throw ItemNotFoundException("Item not found by ID: " + id);
    }

    (*it)->setItemStr(itemStr) ;
}


void GradingCriteria::updateCriteriaItem(EvalItem::ItemUniqueIdType id, CriteriaItem::CriteriaItemLevelType level)
{
    std::vector<boost::shared_ptr<CriteriaItem> >::iterator it ;

    it = std::find_if(m_criteriaItems.begin(), m_criteriaItems.end(), hasId(id)) ;

    if(it == m_criteriaItems.end())
    {
        throw ItemNotFoundException("Item not found by ID: " + id);
    }

    (*it)->setCriteriaItemLevelValue(level) ;
}


void GradingCriteria::updateCriteriaItem(EvalItem::ItemUniqueIdType id, std::string itemStr, CriteriaItem::CriteriaItemLevelType level)
{
    std::vector<boost::shared_ptr<CriteriaItem> >::iterator it ;

    it = std::find_if(m_criteriaItems.begin(), m_criteriaItems.end(), hasId(id)) ;

    if(it == m_criteriaItems.end())
    {
        throw ItemNotFoundException("Item not found by ID: " + id);
    }

    (*it)->setItemStr(itemStr) ;
    (*it)->setCriteriaItemLevelValue(level) ;
}


void GradingCriteria::acceptChildren(Visitor& visitor)
{
    BOOST_FOREACH(boost::shared_ptr<CriteriaItem> ci, m_criteriaItems)
    {
        ci->accept(visitor);
    }
}




