// (C) Copyright Steven Hurd 2013

#include "evalitem.h"

EvalItem::ItemUniqueIdType EvalItem::s_itemCounter = 0;

EvalItem::EvalItem(std::string str, bool editable) :
    m_itemEditable(editable), m_itemStr(str)
{
    m_uniqueItemId = s_itemCounter++;
}
