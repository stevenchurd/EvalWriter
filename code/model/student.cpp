// (C) Copyright Steven Hurd 2013

#include "student.h"
#include "eval.h"

#include "boost/shared_ptr.hpp"


Student::Student(std::string firstName, std::string middleName, std::string lastName,
                 boost::uuids::uuid objUuid) :
    VisitorElement(),
    m_firstName(firstName),
    m_middleName(middleName),
    m_lastName(lastName),
    m_uuid(objUuid)
{
}


std::vector<boost::shared_ptr<Eval> >::const_iterator Student::evalsBegin()
{
    return m_evals.begin();
}


std::vector<boost::shared_ptr<Eval> >::const_iterator Student::evalsEnd()
{
    return m_evals.end();
}


void Student::addEval(boost::shared_ptr<Eval> newEval)
{
    m_evals.push_back(newEval) ;
}


std::vector<boost::shared_ptr<Course> >::const_iterator Student::coursesBegin()
{
    return m_courses.begin();
}


std::vector<boost::shared_ptr<Course> >::const_iterator Student::coursesEnd()
{
    return m_courses.end();
}


void Student::addCourse(boost::shared_ptr<Course> course)
{
    m_courses.push_back(course) ;
}


bool Student::isInCourse(boost::shared_ptr<Course> course) const
{
    return (std::find(m_courses.begin(), m_courses.end(), course) != m_courses.end());
}


void Student::acceptChildren(Visitor& visitor)
{
    std::for_each(m_courses.begin(), m_courses.end(),
                  [&visitor](boost::shared_ptr<Course> course) { course->accept(visitor); });

    std::for_each(m_evals.begin(), m_evals.end(),
                  [&visitor](boost::shared_ptr<Eval> eval) { eval->accept(visitor); });
}
