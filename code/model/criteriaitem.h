// (C) Copyright Steven Hurd 2013

#ifndef CRITERIAITEM_H
#define CRITERIAITEM_H

#include <string>
#include "evalitem.h"
#include "model/visitors/visitor.h"

class CriteriaItem : public EvalItem
{
public:
    enum CriteriaItemLevelType{
        EXCELLENT,
        GOOD,
        AVERAGE,
        BELOW_AVERAGE,
        POOR
    };
    static_assert(INVALID_ITEM_LEVEL != EXCELLENT, "INVALID_ITEM_LEVEL must not be the same as the first enum value.");

    CriteriaItem(std::string parentName, std::string itemStr, CriteriaItemLevelType level);

    // virtual override functions
    virtual std::string getItemTitleStr(void) const override { return getParentCriteriaName(); }
    virtual int getItemLevel(void) const override { return getCriteriaItemLevel(); }

    std::string getParentCriteriaName(void) const { return m_parentCriteriaName; }

    void setCriteriaItemLevelValue(CriteriaItemLevelType level) { m_criteriaItemLevel = level; }
    CriteriaItemLevelType getCriteriaItemLevel(void) const { return m_criteriaItemLevel; }

    /*
     * VisitorElement functions
     */
    void accept(Visitor& visitor) { visitor.visit(*this); }

private:
    std::string m_parentCriteriaName;
    CriteriaItemLevelType m_criteriaItemLevel;

    // disable copy constructor and assignment
    CriteriaItem(const CriteriaItem&);
    CriteriaItem& operator= (const CriteriaItem&);


};


/*
 * Predicate definitions
 */

class findCriteriaItem : public findEvalItem
{
protected:
    std::string m_parentName;
    CriteriaItem::CriteriaItemLevelType m_level;

public:
    findCriteriaItem(std::string itemName, std::string parentName,
                 CriteriaItem::CriteriaItemLevelType level) :
        findEvalItem(itemName), m_parentName(parentName), m_level(level) {}
    virtual ~findCriteriaItem() {}

    bool operator() (const CriteriaItem& criteriaItem) {
        return (criteriaItem.getItemStr() == m_itemName &&
                criteriaItem.getParentCriteriaName() == m_parentName &&
                criteriaItem.getCriteriaItemLevel() == m_level);
    }

    bool operator() (const boost::shared_ptr<CriteriaItem>& criteriaItem) {
        return (criteriaItem->getItemStr() == m_itemName &&
                criteriaItem->getParentCriteriaName() == m_parentName &&
                criteriaItem->getCriteriaItemLevel() == m_level);
    }
};



#endif // CRITERIAITEM_H
