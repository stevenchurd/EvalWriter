// (C) Copyright Steven Hurd 2013

#ifndef GRADINGCRITERIA_H
#define GRADINGCRITERIA_H

#include <vector>
#include "criteriaitem.h"

#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>


class GradingCriteria : public VisitorElement
{
public:
    GradingCriteria(std::string criteriaName,
                    boost::uuids::uuid objUuid = boost::uuids::random_generator()());
    virtual ~GradingCriteria() {}

    std::string getCriteriaName(void) const { return m_criteriaName; }
    void setCriteriaName(const std::string name) { m_criteriaName = name; }

    void addCriteriaItem(std::string descStr,
                        CriteriaItem::CriteriaItemLevelType level) ;

    void addExistingCriteriaItem(std::string descStr,
                        CriteriaItem::CriteriaItemLevelType level,
                        boost::uuids::uuid objUuid) ;

    boost::shared_ptr<CriteriaItem> getCriteriaItemAt(unsigned int index) const;
    bool getCriteriaItemById(std::string id, boost::shared_ptr<CriteriaItem> &gc) const;

    int getNumCriteriaItems(void) const;

    void removeCriteriaItemAt(unsigned int pos);

    std::string getUuid(void) const { return to_string(m_uuid); }

    /*
     * VisitorElement functions
     */
    void accept(Visitor& visitor) { visitor.visit(*this); }
    void acceptChildren(Visitor& visitor);

private:
    std::string m_criteriaName ;
    std::vector<boost::shared_ptr<CriteriaItem> > m_criteriaItems;

    boost::uuids::uuid m_uuid;

    // disable copy constructor and assignment
    GradingCriteria(const GradingCriteria&);
    GradingCriteria& operator= (const GradingCriteria&);
};


#endif // GRADINGCRITERIA_H
