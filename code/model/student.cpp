// (C) Copyright Steven Hurd 2013

#include "student.h"
#include "eval.h"

#include "boost/shared_ptr.hpp"

Student::UniqueStudentId Student::s_idCounter = 0;


Student::Student(std::string firstName, std::string middleName, std::string lastName) : VisitorElement(),
    m_firstName(firstName), m_middleName(middleName), m_lastName(lastName)
{
    m_id = s_idCounter++ ;
}

boost::shared_ptr<Eval> Student::addEval(std::string evalName)
{
    boost::shared_ptr<Eval> eval(new Eval(evalName)) ;

    m_evals.push_back(eval) ;

    return eval;
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
