#ifndef REPLACECRITERIAITEMVISITOR_H
#define REPLACECRITERIAITEMVISITOR_H

#include "visitor.h"

#include "model/evalitem.h"

class Student;
class Eval;
class Course;

class ReplaceCriteriaItemVisitor : public Visitor
{
public:
    ReplaceCriteriaItemVisitor(boost::shared_ptr<EvalItem> newEvalItem, std::string oldUuid);

    void visit(Student& );
    void visit(Eval& );
    void visit(Course& ) {} // do nothing

private:
    boost::shared_ptr<EvalItem> m_newEvalItem;
    std::string m_oldUuid;
};

#endif // REPLACECRITERIAITEMVISITOR_H
