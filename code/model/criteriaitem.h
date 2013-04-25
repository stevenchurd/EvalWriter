// (C) Copyright Steven Hurd 2013

#ifndef CRITERIAITEM_H
#define CRITERIAITEM_H

#include <string>
#include "evalitem.h"

#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>

class Visitor;

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

    CriteriaItem(std::string parentName, std::string itemStr, CriteriaItemLevelType level,
                 boost::uuids::uuid objUuid = boost::uuids::random_generator()());

    // virtual override functions
    virtual std::string getItemTitleStr(void) const override { return getParentCriteriaName(); }
    virtual int getItemLevel(void) const override { return getCriteriaItemLevel(); }

    std::string getParentCriteriaName(void) const { return m_parentCriteriaName; }

    void setCriteriaItemLevelValue(CriteriaItemLevelType level) { m_criteriaItemLevel = level; }
    CriteriaItemLevelType getCriteriaItemLevel(void) const { return m_criteriaItemLevel; }

    /*
     * VisitorElement functions
     */
    void accept(Visitor& visitor);

private:
    std::string m_parentCriteriaName;
    CriteriaItemLevelType m_criteriaItemLevel;

    // disable copy constructor and assignment
    CriteriaItem(const CriteriaItem&);
    CriteriaItem& operator= (const CriteriaItem&);


};


bool operator<(const boost::shared_ptr<CriteriaItem>& rhs, const boost::shared_ptr<CriteriaItem>& lhs);

#endif // CRITERIAITEM_H
