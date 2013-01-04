// (C) Copyright Steven Hurd 2013

#include "gradingcriteriasavevisitor.h"
#include "model/criteriaitem.h"
#include "model/gradingcriteria.h"
#include "xmlnodenames.h"
#include <boost/property_tree/ptree.hpp>


void GradingCriteriaSaveVisitor::visit(GradingCriteria& gc)
{
    m_gradingCriteriaItemPt.put(elementNameNode, gc.getCriteriaName());

	// first visit the children of the grading criteria which
	// is all the criteria items
	gc.acceptChildren(*this);

	// then save the grading criteria object info itself
    m_pt.add_child(gradingCriteriaRootNode + separator + singleGradingCriteriaNode, m_gradingCriteriaItemPt);

	// finally, clear the grading criteria item so the next one can use it
	m_gradingCriteriaItemPt.clear();
}


void GradingCriteriaSaveVisitor::visit(CriteriaItem& ci)
{
    boost::property_tree::ptree ciPt;
    ciPt.add(elementNameNode, ci.getItemStr());
    ciPt.add(criteriaItemLevelNode, ci.getCriteriaItemLevel()) ;

    m_gradingCriteriaItemPt.add_child(singleCriteriaItemNode, ciPt);
}


