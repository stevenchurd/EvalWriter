// (C) Copyright Steven Hurd 2013

#include "criteriaitem.h"
#include "visitors/visitor.h"

CriteriaItem::CriteriaItem(std::string parentName, std::string itemStr, CriteriaItemLevelType level,
                           boost::uuids::uuid objUuid) :
    EvalItem(itemStr, false, objUuid), m_parentCriteriaName(parentName), m_criteriaItemLevel(level)
{
}


void CriteriaItem::accept(Visitor& visitor)
{
    visitor.visit(*this);
}


bool operator<(const boost::shared_ptr<CriteriaItem>& rhs, const boost::shared_ptr<CriteriaItem>& lhs)
{
    if(rhs->getCriteriaItemLevel() == lhs->getCriteriaItemLevel())
        return (rhs->getItemStr() < lhs->getItemStr());
    else
        return (rhs->getCriteriaItemLevel() < lhs->getCriteriaItemLevel());
}

