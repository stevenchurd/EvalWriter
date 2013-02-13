// (C) Copyright Steven Hurd 2013

#ifndef GRADINGCRITERIA_H
#define GRADINGCRITERIA_H

#include <vector>
#include "criteriaitem.h"

class GradingCriteria : public VisitorElement
{
public:
    GradingCriteria(std::string criteriaName);
    virtual ~GradingCriteria() {}

    std::string getCriteriaName(void) const { return m_criteriaName; }
    void setCriteriaName(const std::string name) { m_criteriaName = name; }

    EvalItem::ItemUniqueIdType addCriteriaItem(std::string descStr,
                        CriteriaItem::CriteriaItemLevelType level) ;

    boost::shared_ptr<CriteriaItem> getCriteriaItem(
            std::string criteriaName,
            CriteriaItem::CriteriaItemLevelType level);

    boost::shared_ptr<CriteriaItem> getCriteriaItem(unsigned int index);

    int getNumCriteriaItems(void);

    void removeCriteriaItem(EvalItem::ItemUniqueIdType id) ;
    void removeCriteriaItemAt(unsigned int pos);

    void updateCriteriaItem(EvalItem::ItemUniqueIdType id, std::string itemStr) ;
    void updateCriteriaItem(EvalItem::ItemUniqueIdType id, CriteriaItem::CriteriaItemLevelType level) ;
    void updateCriteriaItem(EvalItem::ItemUniqueIdType id, std::string itemStr, CriteriaItem::CriteriaItemLevelType level) ;

    /*
     * VisitorElement functions
     */
    void accept(Visitor& visitor) { visitor.visit(*this); }
    void acceptChildren(Visitor& visitor);

private:
    std::string m_criteriaName ;
    std::vector<boost::shared_ptr<CriteriaItem> > m_criteriaItems;

    // disable copy constructor and assignment
    GradingCriteria(const GradingCriteria&);
    GradingCriteria& operator= (const GradingCriteria&);
};



/*
 * Predicate definitions
 */

class hasGradingCriteriaItem {
    std::string m_gcName;
public:
    hasGradingCriteriaItem(std::string gcName) :
        m_gcName(gcName) {}
    bool operator()(const GradingCriteria& gc) {
        return (gc.getCriteriaName() == m_gcName);
    }
    bool operator()(const boost::shared_ptr<GradingCriteria>& gc) {
        return (gc->getCriteriaName() == m_gcName);
    }
};






#endif // GRADINGCRITERIA_H
