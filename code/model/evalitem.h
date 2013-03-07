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
    static const int INVALID_ITEM_LEVEL = -1;

    EvalItem(std::string str, bool editable = false);
    virtual ~EvalItem() {}

    virtual std::string getItemTitleStr(void) const { return ""; }
    virtual void setItemTitleStr(const std::string title){}

    virtual int getItemLevel(void) const { return INVALID_ITEM_LEVEL; }
    bool isItemEditable(void) const { return m_itemEditable; }

    std::string getItemStr(void) const { return m_itemStr; }
    void setItemStr(const std::string str) { m_itemStr = str; }


    ItemUniqueIdType getUniqueId(void) const { return m_uniqueItemId; }

private:
    static ItemUniqueIdType s_itemCounter ;
    int m_uniqueItemId;
    std::string m_itemStr;
    bool m_itemEditable;

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

class hasId {
    EvalItem::ItemUniqueIdType m_id;
public:
    hasId(EvalItem::ItemUniqueIdType id) : m_id(id){}
    bool operator()(const EvalItem& item) {
        return (item.getUniqueId() == this->m_id);
    }
    bool operator()(const boost::shared_ptr<EvalItem>& item) {
        return (item->getUniqueId() == this->m_id);
    }
};

#endif // EVALITEM_H
