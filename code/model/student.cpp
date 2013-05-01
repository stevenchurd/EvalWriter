// (C) Copyright Steven Hurd 2013

#include "student.h"
#include "eval.h"
#include "course.h"
#include "visitors/visitor.h"

#include "boost/shared_ptr.hpp"


Student::Student(std::string firstName, std::string middleName, std::string lastName,
                 Gender gender, boost::uuids::uuid objUuid) :
    VisitorElement(),
    m_firstName(firstName),
    m_middleName(middleName),
    m_lastName(lastName),
    m_gender(gender),
    m_uuid(objUuid)
{
}


void Student::updateName(std::string firstName, std::string middleName, std::string lastName)
{
    m_firstName = firstName;
    m_middleName = middleName;
    m_lastName = lastName;
}


void Student::updateGender(Gender gender)
{
    m_gender = gender;
}


std::vector<boost::shared_ptr<Eval> >::const_iterator Student::evalsBegin() const
{
    return m_evals.cbegin();
}


std::vector<boost::shared_ptr<Eval> >::const_iterator Student::evalsEnd() const
{
    return m_evals.cend();
}


unsigned int Student::addEval(boost::shared_ptr<Eval> newEval)
{
    auto it = std::find_if(m_evals.begin(), m_evals.end(),
                           [&newEval] (boost::shared_ptr<Eval> eval)
                           { return (newEval < eval); });

    unsigned int row = std::distance(m_evals.begin(), it);
    m_evals.insert(it, newEval);
    return row;
}


bool Student::getEvalById(std::string id, boost::shared_ptr<Eval>& eval) const
{
    auto it = std::find_if(m_evals.begin(), m_evals.end(),
                           [&id] (boost::shared_ptr<Eval> myEval) { return (myEval->getUuid() == id); });


    if(it != m_evals.end())
    {
        eval = *it;
        return true;
    }

    return false;
}


bool Student::hasEval(std::string id) const
{
    auto it = std::find_if(m_evals.begin(), m_evals.end(),
                           [&id] (boost::shared_ptr<Eval> eval)
                           {
                               return (eval->getUuid() == id);
                           });

    return it != m_evals.end();
}


void Student::removeEval(std::vector<boost::shared_ptr<Eval> >::const_iterator it)
{
    m_evals.erase(it);
}


std::vector<boost::shared_ptr<Course> >::const_iterator Student::coursesBegin() const
{
    return m_courses.cbegin();
}


std::vector<boost::shared_ptr<Course> >::const_iterator Student::coursesEnd() const
{
    return m_courses.cend();
}


unsigned int Student::addCourse(boost::shared_ptr<Course> newCourse)
{
    auto it = std::find_if(m_courses.begin(), m_courses.end(),
                           [&newCourse] (boost::shared_ptr<Course> course)
                           { return (newCourse < course); });

    unsigned int row = std::distance(m_courses.begin(), it);
    m_courses.insert(it, newCourse);
    return row;
}


void Student::removeCourse(std::string uuid)
{
    m_courses.erase(std::remove_if(m_courses.begin(), m_courses.end(),
                                   [&uuid] (boost::shared_ptr<Course> course)
                                   { return (course->getUuid() == uuid ); }),
                    m_courses.end());
}


void Student::removeCourse(std::vector<boost::shared_ptr<Course> >::const_iterator it)
{
    m_courses.erase(it);
}


bool Student::isInCourse(boost::shared_ptr<Course> course) const
{
    return (std::find(m_courses.begin(), m_courses.end(), course) != m_courses.end());
}


void Student::accept(Visitor& visitor)
{
    visitor.visit(*this);
}


void Student::acceptChildren(Visitor& visitor)
{
    std::for_each(m_courses.begin(), m_courses.end(),
                  [&visitor](boost::shared_ptr<Course> course) { course->accept(visitor); });

    std::for_each(m_evals.begin(), m_evals.end(),
                  [&visitor](boost::shared_ptr<Eval> eval) { eval->accept(visitor); });
}


bool Student::operator==(const Student& rhs) const
{
    return (getUuid() == rhs.getUuid());
}


bool operator<(const boost::shared_ptr<Student>& lhs, const boost::shared_ptr<Student>& rhs)
{
    return lhs->getDisplayName() < rhs->getDisplayName();
}
