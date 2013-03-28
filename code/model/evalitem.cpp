// (C) Copyright Steven Hurd 2013

#include "evalitem.h"

EvalItem::EvalItem(std::string str, bool editable,
                   boost::uuids::uuid objUuid) :
    VisitorElement(),
    m_itemEditable(editable), m_itemStr(str), m_uuid(objUuid)
{
}
