// (C) Copyright Steven Hurd 2013

#ifndef _GRADINGCRITERIASAVEVISITOR_H_
#define _GRADINGCRITERIASAVEVISITOR_H_

#include "savevisitor.h"
#include <boost/property_tree/ptree.hpp>

class GradingCriteria;
class CriteriaItem;

class GradingCriteriaSaveVisitor : public SaveVisitor
{
	public:
        GradingCriteriaSaveVisitor(boost::property_tree::ptree& parentPt);
		virtual ~GradingCriteriaSaveVisitor() {}

		void visit(GradingCriteria& gc);
		
		void visit(CriteriaItem& criteriaItem);

	private:
        boost::property_tree::ptree m_gradingCriteriaItemPt;

};


#endif

