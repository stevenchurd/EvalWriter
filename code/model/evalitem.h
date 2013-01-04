// (C) Copyright Steven Hurd 2013

#ifndef EVALITEM_H
#define EVALITEM_H

#include <string>
#include <functional>
#include "visitors/visitorelement.h"
#include <boost/shared_ptr.hpp>

class EvalItem : public VisitorElement
{
public:
    typedef unsigned int ItemUniqueIdType ;

    /*
     * Constructors/destructor
     */
    EvalItem(std::string str) : m_itemStr(str)
    {
        m_uniqueItemId = s_itemCounter++;
    }

    virtual ~EvalItem() {}

    std::string getItemStr(void) const { return m_itemStr; }
    void setItemStr(std::string str) { m_itemStr = str; }

    ItemUniqueIdType getUniqueId(void) const { return m_uniqueItemId; }

    class hasId {
        ItemUniqueIdType m_id;
    public:
        hasId(ItemUniqueIdType id) : m_id(id){}
        bool operator()(const EvalItem& item) {
            return (item.getUniqueId() == this->m_id);
        }
        bool operator()(const boost::shared_ptr<EvalItem>& item) {
            return (item->getUniqueId() == this->m_id);
        }
    };

protected:
    std::string m_itemStr;

private:
    static ItemUniqueIdType s_itemCounter ;
    int m_uniqueItemId;

    // disable copy constructor and assignment
    EvalItem(const EvalItem&);
    EvalItem& operator= (const EvalItem&);
};


/*
 * Predicate definitions
 */

class findEvalItem
{
protected:
    std::string m_itemName;

public:
    findEvalItem(std::string itemName) :
        m_itemName(itemName) {}
    virtual ~findEvalItem(){}
    bool operator() (const EvalItem& evalItem) {
        return (evalItem.getItemStr() == m_itemName);
    }
};



#endif // EVALITEM_H
