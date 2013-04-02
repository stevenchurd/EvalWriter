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
    void addEval(boost::shared_ptr<Eval> newEval) ;
    int getNumEvals(void) { return m_evals.size(); }
    std::vector<boost::shared_ptr<Eval> >::const_iterator evalsBegin() const;
    std::vector<boost::shared_ptr<Eval> >::const_iterator evalsEnd() const;
    bool getEvalById(std::string id, boost::shared_ptr<Eval>& eval) const;

    /*
     * Course functions
     */
    std::vector<boost::shared_ptr<Course> >::const_iterator coursesBegin() const;
    std::vector<boost::shared_ptr<Course> >::const_iterator coursesEnd() const;
    void addCourse(boost::shared_ptr<Course> course) ;
    void removeCourse(std::string uuid);
    void removeCourse(std::vector<boost::shared_ptr<Course> >::const_iterator it);
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

#endif // STUDENT_H
