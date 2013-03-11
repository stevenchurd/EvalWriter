// (C) Copyright Steven Hurd 2013

#ifndef CUSTOMTEXTITEM_H
#define CUSTOMTEXTITEM_H

#include "evalitem.h"
#include "model/visitors/visitor.h"

class CustomTextItem : public EvalItem
{
public:
    CustomTextItem(std::string title, std::string text) : EvalItem(text, true), m_title(title) {}
    virtual ~CustomTextItem() {}

    // virtual override functions
    virtual std::string getItemTitleStr(void) const { return m_title; }
    virtual void setItemTitleStr(const std::string title) { m_title = title; }

    /*
     * VisitorElement functions
     */
    void accept(Visitor& visitor) { visitor.visit(*this); }

private:
    std::string m_title;

    // disable copy constructor and assignment
    CustomTextItem(const CustomTextItem&);
    CustomTextItem& operator= (const CustomTextItem&);
};

#endif // CUSTOMTEXTITEM_H
