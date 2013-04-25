#include "replacecriteriaitemvisitor.h"
#include "model/student.h"
#include "model/eval.h"
#include "model/evalitem.h"

ReplaceCriteriaItemVisitor::ReplaceCriteriaItemVisitor(boost::shared_ptr<EvalItem> evalItem,
                                                       std::string oldUuid) :
    Visitor(), m_newEvalItem(evalItem), m_oldUuid(oldUuid)
{
}


void ReplaceCriteriaItemVisitor::visit(Student& student)
{
    student.acceptChildren(*this);
}


void ReplaceCriteriaItemVisitor::visit(Eval& eval)
{
    eval.replaceEvalItem(m_newEvalItem, m_oldUuid);
}
