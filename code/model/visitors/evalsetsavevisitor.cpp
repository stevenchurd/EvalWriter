#include "evalsetsavevisitor.h"
#include "model/evalset.h"
#include "model/eval.h"
#include "xmlnodenames.h"


EvalSetSaveVisitor::EvalSetSaveVisitor(boost::property_tree::ptree &parentPt) :
    SaveVisitor(parentPt)
{
}


void EvalSetSaveVisitor::visit(EvalSet& evalSet)
{
    //always construct the EvalSet tree as a child of the back of the m_subTrees list
    boost::property_tree::ptree evalSetPt;

    // put the evalSet title in before visiting the subtrees
    evalSetPt.put(xml_node_names::elementUuidNode, evalSet.getUuid());
    evalSetPt.put(xml_node_names::elementTitleNode, evalSet.getEvalSetName());

    m_subTrees.push_back(evalSetPt);

    evalSet.acceptChildren(*this);

    // after returning, pop the last element and add it to the one before
    evalSetPt = m_subTrees.back();
    m_subTrees.pop_back();
    if(m_subTrees.empty())
    {
        m_pt.add_child(xml_node_names::evalSetsRootNode +
                       xml_node_names::separator +
                       xml_node_names::singleEvalSetNode, evalSetPt);
    }
    else
    {
        m_subTrees.back().add_child(xml_node_names::singleEvalSetNode, evalSetPt);
    }
}


void EvalSetSaveVisitor::visit(Eval& eval)
{
    boost::property_tree::ptree evalPt;

    // add the GUID of the eval
    evalPt.add(xml_node_names::elementUuidNode, eval.getUuid());
    m_subTrees.back().add_child(xml_node_names::singleEvalNode, evalPt);
}
