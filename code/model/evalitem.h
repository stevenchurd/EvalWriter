// (C) Copyright Steven Hurd 2013

#ifndef EVALITEM_H
#define EVALITEM_H

#include <string>
#include <functional>
#include "visitors/visitorelement.h"

#include <boost/shared_ptr.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>

class EvalItem : public VisitorElement
{
public:
    /*
     * Constructors/destructor
     */
    static const int INVALID_ITEM_LEVEL = -1;

    EvalItem(std::string str, bool editable = false,
             boost::uuids::uuid objUuid = boost::uuids::random_generator()());
    virtual ~EvalItem() {}

    virtual std::string getItemTitleStr(void) const { return ""; }
    virtual void setItemTitleStr(const std::string title){}

    virtual int getItemLevel(void) const { return INVALID_ITEM_LEVEL; }
    bool isItemEditable(void) const { return m_itemEditable; }

    std::string getItemStr(void) const { return m_itemStr; }
    void setItemStr(const std::string str) { m_itemStr = str; }

    std::string getUuid(void) const { return to_string(m_uuid); }

private:
    std::string m_itemStr;
    bool m_itemEditable;

    boost::uuids::uuid m_uuid;

    // disable copy constructor and assignment
    EvalItem(const EvalItem&);
    EvalItem& operator= (const EvalItem&);
};

#endif // EVALITEM_H
