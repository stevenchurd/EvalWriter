// (C) Copyright Steven Hurd 2013

#ifndef COURSE_H
#define COURSE_H


#include <list>
#include <boost/shared_ptr.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include "student.h"



class Course : public VisitorElement
{
public:
    Course(std::string courseName, boost::uuids::uuid objUuid = boost::uuids::random_generator()());
    virtual ~Course() {}

    void updateCourseName(std::string newName) ;
    std::string getCourseName(void) const { return m_name; }
    std::string getUuid(void) const { return to_string(m_uuid); }

    /*
     * VisitorElement interface functions
     */
    void accept(Visitor& visitor) { visitor.visit(*this); }


private:

    std::string m_name ;
    boost::uuids::uuid m_uuid;

    // disable copy constructor and assignment
    Course(const Course&);
    Course& operator= (const Course&);
};


/*
 * Predicate definitions
 */

class hasCourseName {
    std::string m_courseName;
public:
    hasCourseName(std::string courseName) :
        m_courseName(courseName) {}
    bool operator()(const Course& course) {
        return (course.getCourseName() == m_courseName);
    }
    bool operator()(const boost::shared_ptr<Course>& course) {
        return (course->getCourseName() == m_courseName);
    }

};


#endif // COURSE_H
