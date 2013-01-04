// (C) Copyright Steven Hurd 2013

#ifndef STUDENTSAVEVISITOR_H
#define STUDENTSAVEVISITOR_H

#include "savevisitor.h"

class Student;
class Course;
class Eval;
class CriteriaItem;
class CustomTextItem;

class StudentSaveVisitor : public SaveVisitor
{
public:
    StudentSaveVisitor();
    virtual ~StudentSaveVisitor() {}

    void visit(Student& );
    void visit(Course& );
    void visit(Eval& );
    void visit(CriteriaItem& );
    void visit(CustomTextItem& );

private:

    boost::property_tree::ptree m_coursesPt;
    boost::property_tree::ptree m_evalsPt;
    boost::property_tree::ptree m_evalItemsPt;

};


#endif // STUDENTSAVEVISITOR_H
