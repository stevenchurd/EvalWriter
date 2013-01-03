
#include <boost/foreach.hpp>
#include "student.h"
#include "eval.h"

Student::UniqueStudentId Student::s_idCounter = 0;


Student::Student(std::string firstName, std::string middleName, std::string lastName) :
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


void Student::acceptChildren(Visitor& visitor)
{
    BOOST_FOREACH(boost::shared_ptr<Course> course, m_courses)
    {
        course->accept(visitor);
    }

    BOOST_FOREACH(boost::shared_ptr<Eval> eval, m_evals)
    {
        eval->accept(visitor);
    }
}
