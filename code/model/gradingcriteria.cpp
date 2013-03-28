// (C) Copyright Steven Hurd 2013

#include <algorithm>
#include <sstream>
#include "gradingcriteria.h"
#include "criteriaitem.h"

GradingCriteria::GradingCriteria(std::string criteriaName,
                                 boost::uuids::uuid objUuid) :
    VisitorElement(),
    m_criteriaName(criteriaName),
    m_uuid(objUuid)
{
}

void GradingCriteria::addCriteriaItem(std::string descStr, CriteriaItem::CriteriaItemLevelType level)
{
    boost::shared_ptr<CriteriaItem> ci(new CriteriaItem(m_criteriaName, descStr, level));
    m_criteriaItems.push_back(ci);
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
    auto it = std::find_if(m_criteriaItems.begin(),
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


bool GradingCriteria::getCriteriaItemById(std::string id, boost::shared_ptr<CriteriaItem>& gc) const
{
    auto it = std::find_if(m_criteriaItems.begin(), m_criteriaItems.end(),
                           [&id] (boost::shared_ptr<CriteriaItem> ci) { return (ci->getUuid() == id); });


    if(it != m_criteriaItems.end())
    {
        gc = *it;
        return true;
    }

    return false;
}


void GradingCriteria::acceptChildren(Visitor& visitor)
{
    std::for_each(m_criteriaItems.begin(), m_criteriaItems.end(),
                  [&visitor](boost::shared_ptr<CriteriaItem> ci) {
                      ci->accept(visitor);
                  });
}




