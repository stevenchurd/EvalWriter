// (C) Copyright Steven Hurd 2013

#include "course.h"
#include "visitors/visitor.h"

Course::Course(std::string courseName, boost::uuids::uuid objUuid) : VisitorElement(),
    m_name(courseName), m_uuid(objUuid)
{
}

void Course::updateCourseName(std::string newName)
{
    m_name = newName ;
}


void Course::accept(Visitor& visitor)
{
    visitor.visit(*this);
}


bool Course::operator==(const Course& rhs) const
{
    return (rhs.getUuid() == this->getUuid());
}


bool operator<(const boost::shared_ptr<Course>& lhs, const boost::shared_ptr<Course>& rhs)
{
    return (lhs->getCourseName() < rhs->getCourseName());
}
