
#include "coursesavevisitor.h"
#include "model/course.h"
#include "xmlnodenames.h"


void CourseSaveVisitor::visit(Course& course)
{
    m_pt.add(coursesRootNode + separator + singleCourseNode, course.getCourseName());
}



