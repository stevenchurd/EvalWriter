#ifndef CUSTOMTEXTITEM_H
#define CUSTOMTEXTITEM_H

#include "evalitem.h"
#include "model/visitors/visitor.h"

class CustomTextItem : public EvalItem
{
public:
    CustomTextItem(std::string text) : EvalItem(text) {}
    virtual ~CustomTextItem() {}

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
