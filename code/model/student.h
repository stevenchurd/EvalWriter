// (C) Copyright Steven Hurd 2013

#ifndef STUDENT_H
#define STUDENT_H

#include <vector>
#include "visitors/visitorelement.h"
#include "visitors/visitor.h"
#include "course.h"

#include <boost/shared_ptr.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>


//forward declarations
class Eval;

class Student : public VisitorElement
{
public:

    /*
     * Constructors/destructor
     */
    Student(std::string firstName, std::string middleName, std::string lastName,
            boost::uuids::uuid objUuid = boost::uuids::random_generator()());
    virtual ~Student() {}

    std::string getFirstName(void) const { return m_firstName; }
    std::string getMiddleName(void) const { return m_middleName; }
    std::string getLastName(void) const { return m_lastName; }
    std::string getDisplayName(void) const {
        if(m_middleName.length() == 0)
            return m_firstName + " " + m_lastName;

        return m_firstName + " " + m_middleName + " " + m_lastName;
    }

    std::string getUuid(void) const { return to_string(m_uuid); }

    /*
     * Eval functions
     */
    boost::shared_ptr<Eval> addEval(std::string evalName) ;
    int getNumEvals(void) { return m_evals.size(); }
    std::vector<boost::shared_ptr<Eval> >::const_iterator evalsBegin();
    std::vector<boost::shared_ptr<Eval> >::const_iterator evalsEnd();

    /*
     * Course functions
     */
    template <typename OutputIterator>
    void getCourseNames(OutputIterator dest);

    std::vector<boost::shared_ptr<Course> >::const_iterator coursesBegin();
    std::vector<boost::shared_ptr<Course> >::const_iterator coursesEnd();
    void addCourse(boost::shared_ptr<Course> course) ;
    bool isInCourse(boost::shared_ptr<Course> course) const;

    /*
     * VisitorElement functions
     */
    void accept(Visitor& visitor) { visitor.visit(*this); }
    void acceptChildren(Visitor& visitor);

private:

    std::string m_firstName ;
    std::string m_lastName ;
    std::string m_middleName ;

    std::vector<boost::shared_ptr<Eval> > m_evals ;
    std::vector<boost::shared_ptr<Course> > m_courses ;

    boost::uuids::uuid m_uuid;

    // disable copy constructor and assignment
    Student(const Student&);
    Student& operator= (const Student&);

};


template <typename OutputIterator>
void Student::getCourseNames(OutputIterator dest)
{
    std::for_each(m_courses.begin(), m_courses.end(),
                  [&dest] (boost::shared_ptr<Course> course)
    {
        dest++ = course->getCourseName();
    });
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
