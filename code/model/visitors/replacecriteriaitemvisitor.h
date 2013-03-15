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
    ReplaceCriteriaItemVisitor(boost::shared_ptr<EvalItem> newEvalItem, int oldId);

    void visit(Student& );
    void visit(Eval& );
    void visit(Course& ) {} // do nothing

private:
    boost::shared_ptr<EvalItem> m_newEvalItem;
    int m_oldId;
};

#endif // REPLACECRITERIAITEMVISITOR_H
