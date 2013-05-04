// (C) Copyright Steven Hurd 2013

#ifndef _COURSESAVEVISITOR_H_
#define _COURSESAVEVISITOR_H_

#include "savevisitor.h"

class Course;

class CourseSaveVisitor : public SaveVisitor
{
	public:
        CourseSaveVisitor(boost::property_tree::ptree& parentPt);

		virtual ~CourseSaveVisitor() {}

		void visit(Course& course);
};


#endif

