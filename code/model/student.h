// (C) Copyright Steven Hurd 2013

#ifndef STUDENT_H
#define STUDENT_H

#include <vector>
#include "visitors/visitorelement.h"

#include <boost/shared_ptr.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>


//forward declarations
class Eval;
class Visitor;
class Course;

class Student : public VisitorElement
{
public:
    /* enum types */
    enum Gender { Female, Male };

    /*
     * Constructors/destructor
     */
    Student(std::string firstName, std::string middleName, std::string lastName,
            Gender gender, boost::uuids::uuid objUuid = boost::uuids::random_generator()());
    virtual ~Student() {}


    void updateName(std::string firstName, std::string middleName, std::string lastName);

    std::string getFirstName(void) const { return m_firstName; }
    std::string getMiddleName(void) const { return m_middleName; }
    std::string getLastName(void) const { return m_lastName; }
    std::string getDisplayName(void) const {
        if(m_middleName.length() == 0)
            return m_firstName + " " + m_lastName;

        return m_firstName + " " + m_middleName + " " + m_lastName;
    }

    Gender getGender() const { return m_gender; }

    std::string getUuid(void) const { return to_string(m_uuid); }

    /*
     * Eval functions
     */
    void addEval(boost::shared_ptr<Eval> newEval) ;
    unsigned int getNumEvals(void) { return static_cast<unsigned int>(m_evals.size()); }
    std::vector<boost::shared_ptr<Eval> >::const_iterator evalsBegin() const;
    std::vector<boost::shared_ptr<Eval> >::const_iterator evalsEnd() const;
    bool getEvalById(std::string id, boost::shared_ptr<Eval>& eval) const;
    void removeEval(std::vector<boost::shared_ptr<Eval> >::const_iterator it);

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
    void accept(Visitor& visitor);
    void acceptChildren(Visitor& visitor);

private:

    std::string m_firstName ;
    std::string m_lastName ;
    std::string m_middleName ;
    Gender m_gender;

    std::vector<boost::shared_ptr<Eval> > m_evals ;
    std::vector<boost::shared_ptr<Course> > m_courses ;

    boost::uuids::uuid m_uuid;

    // disable copy constructor and assignment
    Student(const Student&);
    Student& operator= (const Student&);

};

bool operator <(const boost::shared_ptr<Student>& lhs, const boost::shared_ptr<Student>& rhs);

#endif // STUDENT_H
