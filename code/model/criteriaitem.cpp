#include "criteriaitem.h"

CriteriaItem::CriteriaItem(std::string parentName, std::string itemStr, CriteriaItemLevelType level) :
    EvalItem(itemStr), m_parentCriteriaName(parentName), m_criteriaItemLevel(level)
{
}
