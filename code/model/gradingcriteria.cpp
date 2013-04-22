// (C) Copyright Steven Hurd 2013

#include <algorithm>
#include <sstream>
#include "gradingcriteria.h"
#include "criteriaitem.h"
#include "visitors/visitor.h"

GradingCriteria::GradingCriteria(std::string criteriaName,
                                 boost::uuids::uuid objUuid) :
    VisitorElement(),
    m_criteriaName(criteriaName),
    m_uuid(objUuid)
{
}


void GradingCriteria::accept(Visitor& visitor)
{
    visitor.visit(*this);
}


unsigned int GradingCriteria::addCriteriaItem(boost::shared_ptr<CriteriaItem> newCi)
{
    auto it = std::find_if(m_criteriaItems.begin(), m_criteriaItems.end(),
                           [&newCi] (boost::shared_ptr<CriteriaItem> ci)
                           { return (newCi < ci); });

    unsigned int row = std::distance(m_criteriaItems.begin(), it);
    m_criteriaItems.insert(it, newCi);
    return row;
}


void GradingCriteria::removeCriteriaItemAt(unsigned int pos)
{
    if(pos > m_criteriaItems.size())
        throw ItemNotFoundException("Invalid item for removal: " + pos);

    m_criteriaItems.erase(m_criteriaItems.begin() + pos);
}


unsigned int GradingCriteria::getNumCriteriaItems(void) const
{
    return static_cast<unsigned int>(m_criteriaItems.size());
}


boost::shared_ptr<CriteriaItem> GradingCriteria::getCriteriaItemAt(unsigned int index) const
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


bool GradingCriteria::operator==(const GradingCriteria& rhs) const
{
    return (getUuid() == rhs.getUuid());
}


bool operator<(const boost::shared_ptr<GradingCriteria>& rhs, const boost::shared_ptr<GradingCriteria>& lhs)
{
    return (rhs->getCriteriaName() < lhs->getCriteriaName());
}

