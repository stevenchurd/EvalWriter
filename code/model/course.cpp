// (C) Copyright Steven Hurd 2013

#include "course.h"

Course::Course(std::string courseName) :
    m_name(courseName)
{
}

void Course::updateCourseName(std::string newName)
{
    m_name = newName ;
}
