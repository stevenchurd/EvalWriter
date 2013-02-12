#include "replacecriteriaitemvisitor.h"
#include "model/student.h"
#include "model/eval.h"
#include "model/evalitem.h"

ReplaceCriteriaItemVisitor::ReplaceCriteriaItemVisitor(boost::shared_ptr<EvalItem> evalItem, int oldId) :
    Visitor(), m_newEvalItem(evalItem), m_oldId(oldId)
{
}


void ReplaceCriteriaItemVisitor::visit(Student& student)
{
    student.acceptChildren(*this);
}


void ReplaceCriteriaItemVisitor::visit(Eval& eval)
{
    eval.replaceEvalItem(m_newEvalItem, m_oldId);
}
