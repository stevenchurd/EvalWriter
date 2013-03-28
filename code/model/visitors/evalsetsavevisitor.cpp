#include "evalsetsavevisitor.h"
#include "model/evalset.h"
#include "model/eval.h"


EvalSetSaveVisitor::EvalSetSaveVisitor() :
    SaveVisitor()
{
    m_subTrees.push_back(m_pt);
}


void EvalSetSaveVisitor::visit(EvalSet& evalSet)
{
    //always construct the EvalSet tree as a child of the back of the m_subTrees list
    boost::property_tree::ptree evalSetPt;

    assert(m_subTrees.begin() != m_subTrees.end());

    evalSet.acceptChildren(*this);

}


void EvalSetSaveVisitor::visit(Eval& eval)
{
}
