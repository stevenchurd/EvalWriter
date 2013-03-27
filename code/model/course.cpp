// (C) Copyright Steven Hurd 2013

#include "course.h"

Course::Course(std::string courseName, boost::uuids::uuid objUuid) : VisitorElement(),
    m_name(courseName), m_uuid(objUuid)
{
}

void Course::updateCourseName(std::string newName)
{
    m_name = newName ;
}
