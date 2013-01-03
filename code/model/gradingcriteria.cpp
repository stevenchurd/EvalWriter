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
                   EvalItem::hasId(id)) ;
}


int GradingCriteria::getNumCriteriaItems(void)
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


boost::shared_ptr<CriteriaItem> GradingCriteria::getCriteriaItem(unsigned int index)
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

    it = std::find_if(m_criteriaItems.begin(), m_criteriaItems.end(), EvalItem::hasId(id)) ;

    if(it == m_criteriaItems.end())
    {
        throw ItemNotFoundException("Item not found by ID: " + id);
    }

    (*it)->setItemStr(itemStr) ;
}


void GradingCriteria::updateCriteriaItem(EvalItem::ItemUniqueIdType id, CriteriaItem::CriteriaItemLevelType level)
{
    std::vector<boost::shared_ptr<CriteriaItem> >::iterator it ;

    it = std::find_if(m_criteriaItems.begin(), m_criteriaItems.end(), EvalItem::hasId(id)) ;

    if(it == m_criteriaItems.end())
    {
        throw ItemNotFoundException("Item not found by ID: " + id);
    }

    (*it)->setCriteriaItemLevelValue(level) ;
}


void GradingCriteria::updateCriteriaItem(EvalItem::ItemUniqueIdType id, std::string itemStr, CriteriaItem::CriteriaItemLevelType level)
{
    std::vector<boost::shared_ptr<CriteriaItem> >::iterator it ;

    it = std::find_if(m_criteriaItems.begin(), m_criteriaItems.end(), EvalItem::hasId(id)) ;

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




