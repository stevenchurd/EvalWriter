#ifndef _COURSESAVEVISITOR_H_
#define _COURSESAVEVISITOR_H_

#include "savevisitor.h"

class Course;

class CourseSaveVisitor : public SaveVisitor
{
	public:
        CourseSaveVisitor() : SaveVisitor() {}

		virtual ~CourseSaveVisitor() {}

		void visit(Course& course);
};


#endif

