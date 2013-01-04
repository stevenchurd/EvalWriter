// (C) Copyright Steven Hurd 2013

#ifndef STUDENT_H
#define STUDENT_H

#include <list>
#include <boost/shared_ptr.hpp>
#include "visitors/visitorelement.h"
#include "visitors/visitor.h"
#include "course.h"
#include <boost/foreach.hpp>

//forward declarations
class Eval;

class Student : public VisitorElement
{
public:
    typedef unsigned int UniqueStudentId ;

    /*
     * Constructors/destructor
     */
    Student(std::string firstName, std::string middleName, std::string lastName);
    virtual ~Student() {}

    std::string getFirstName(void) const { return m_firstName; }
    std::string getMiddleName(void) const { return m_middleName; }
    std::string getLastName (void) const { return m_lastName; }

    boost::shared_ptr<Eval> addEval(std::string evalName) ;
    void addCourse(boost::shared_ptr<Course> course) ;

    UniqueStudentId getUniqueId(void) { return m_id; }

    template <typename OutputIterator>
    void getCourseNames(OutputIterator dest);

    template <typename OutputIterator>
    void getEvals(OutputIterator dest);

    /*
     * VisitorElement functions
     */
    void accept(Visitor& visitor) { visitor.visit(*this); }
    void acceptChildren(Visitor& visitor);

private:

    std::string m_firstName ;
    std::string m_lastName ;
    std::string m_middleName ;

    std::list<boost::shared_ptr<Eval> > m_evals ;
    std::list<boost::shared_ptr<Course> > m_courses ;

    UniqueStudentId m_id ;
    static UniqueStudentId s_idCounter ;

    // disable copy constructor and assignment
    Student(const Student&);
    Student& operator= (const Student&);

};


template <typename OutputIterator>
void Student::getCourseNames(OutputIterator dest)
{
    BOOST_FOREACH(boost::shared_ptr<Course> course, m_courses)
    {
        dest++ = course->getCourseName();
    }
}


template <typename OutputIterator>
void Student::getEvals(OutputIterator dest)
{
    BOOST_FOREACH(boost::shared_ptr<Eval> eval, m_evals)
    {
        dest++ = eval;
    }
}



/*
 * Predicate definitions
 */

 class hasStudentName {
     std::string m_fn, m_mn, m_ln;
 public:
     hasStudentName(std::string fn, std::string mn, std::string ln) :
         m_fn(fn), m_mn(mn), m_ln(ln) {}
     bool operator()(const Student& student) {
         return (m_fn.compare(student.getFirstName()) &&
                 m_mn.compare(student.getMiddleName()) &&
                 m_ln.compare(student.getLastName()));
     }
 };


#endif // STUDENT_H
