#include "removeevalvisitor.h"
#include "model/evalset.h"

RemoveEvalVisitor::RemoveEvalVisitor(std::vector<std::string> evalUuids) :
    Visitor(), m_evalUuids(evalUuids)
{
}


void RemoveEvalVisitor::visit(EvalSet& evalSet)
{
    evalSet.acceptChildren(*this);

    // remove all evals that match the uuid
    evalSet.removeEval(m_evalUuids);
}

