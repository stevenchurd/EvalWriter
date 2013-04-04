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


bool Course::operator==(const Course& rhs) const
{
    if(rhs.getUuid() == this->getUuid())
        return true;
    else
        return false;
}


bool operator<(const boost::shared_ptr<Course>& lhs, const boost::shared_ptr<Course>& rhs)
{
    return (lhs->getCourseName() < rhs->getCourseName());
}
