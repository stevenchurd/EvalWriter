// (C) Copyright Steven Hurd 2013

#include "customtextitem.h"
#include "visitors/visitor.h"

CustomTextItem::CustomTextItem(std::string title, std::string text, boost::uuids::uuid objUuid) :
    EvalItem(text, true, objUuid),
    m_title(title)
{
}


void CustomTextItem::accept(Visitor& visitor)
{
    visitor.visit(*this);
}
