// (C) Copyright Steven Hurd 2013

#ifndef CUSTOMTEXTITEM_H
#define CUSTOMTEXTITEM_H

#include "evalitem.h"

#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>

class Visitor;

class CustomTextItem : public EvalItem
{
public:
    CustomTextItem(std::string title, std::string text, boost::uuids::uuid objUuid = boost::uuids::random_generator()());
    virtual ~CustomTextItem() {}

    // virtual override functions
    virtual std::string getItemTitleStr(void) const { return m_title; }
    virtual void setItemTitleStr(const std::string title) { m_title = title; }

    /*
     * VisitorElement functions
     */
    void accept(Visitor& visitor);

private:
    std::string m_title;

    // disable copy constructor and assignment
    CustomTextItem(const CustomTextItem&);
    CustomTextItem& operator= (const CustomTextItem&);
};

#endif // CUSTOMTEXTITEM_H
