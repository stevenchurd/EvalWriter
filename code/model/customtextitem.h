// (C) Copyright Steven Hurd 2013

#ifndef CUSTOMTEXTITEM_H
#define CUSTOMTEXTITEM_H

#include "evalitem.h"
#include "model/visitors/visitor.h"

class CustomTextItem : public EvalItem
{
public:
    CustomTextItem(std::string text) : EvalItem(text, true) {}
    virtual ~CustomTextItem() {}

    // virtual override functions
    virtual std::string getItemTitleStr(void) const { return "Custom Text"; }

    /*
     * VisitorElement functions
     */
    void accept(Visitor& visitor) { visitor.visit(*this); }

private:
    // disable copy constructor and assignment
    CustomTextItem(const CustomTextItem&);
    CustomTextItem& operator= (const CustomTextItem&);

};

#endif // CUSTOMTEXTITEM_H
