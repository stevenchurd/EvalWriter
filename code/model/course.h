// (C) Copyright Steven Hurd 2013

#ifndef COURSE_H
#define COURSE_H


#include <list>
#include "visitors/visitorelement.h"

#include <boost/shared_ptr.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>

class Visitor;

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
    void accept(Visitor& visitor);

    bool operator==(const Course&) const;

private:

    std::string m_name ;
    boost::uuids::uuid m_uuid;

    // disable copy constructor and assignment
    Course(const Course&);
    Course& operator= (const Course&);
};

bool operator<(const boost::shared_ptr<Course>& lhs, const boost::shared_ptr<Course>& rhs);

#endif // COURSE_H
