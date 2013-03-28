// (C) Copyright Steven Hurd 2013

#include "customtextitem.h"

CustomTextItem::CustomTextItem(std::string title, std::string text, boost::uuids::uuid objUuid) :
    EvalItem(text, true, objUuid),
    m_title(title)
{
}
