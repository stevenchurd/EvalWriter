#ifndef REMOVEEVALVISITOR_H
#define REMOVEEVALVISITOR_H

#include "visitor.h"
#include <vector>

class EvalSet;
class Eval;

class RemoveEvalVisitor : public Visitor
{
public:
    RemoveEvalVisitor(std::vector<std::string> evalUuids);
    virtual ~RemoveEvalVisitor() {}

    void visit(EvalSet& );
    void visit(Eval& ) {} // do nothing

private:
    std::vector<std::string> m_evalUuids;
};

#endif // REMOVEEVALVISITOR_H
