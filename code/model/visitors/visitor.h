#ifndef VISITOR_H
#define VISITOR_H

#include "evalexceptions.h"
#include <boost/shared_ptr.hpp>
#include <boost/foreach.hpp>
#include <list>

// foward declarations
class Student;
class Course;
class Eval;
class EvalItem;
class GradingCriteria;
class CriteriaItem;
class CustomTextItem;

class Visitor
{
public:
    Visitor() {}
    virtual ~Visitor() {}

    virtual void visit(Student& )
    {
        throw InvalidVisitorException("Student visit not implemented in derived class");
    }

    virtual void visit(Course& )
    {
        throw InvalidVisitorException("Course visit not implemented in derived class");
    }

    virtual void visit(Eval& )
    {
        throw InvalidVisitorException("Eval visit not implemented in derived class");
    }

    virtual void visit(GradingCriteria& )
    {
        throw InvalidVisitorException("GradingCriteria visit not implemented in derived class");
    }

    virtual void visit(CriteriaItem& )
    {
        throw InvalidVisitorException("CriteriaItem visit not implemented in derived class");
    }

    virtual void visit(CustomTextItem& )
    {
        throw InvalidVisitorException("CustomTextItem visit not implemented in derived class");
    }
};

#endif // VISITOR_H
