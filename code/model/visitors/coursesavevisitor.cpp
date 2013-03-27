// (C) Copyright Steven Hurd 2013

#include "coursesavevisitor.h"
#include "model/course.h"
#include "xmlnodenames.h"


void CourseSaveVisitor::visit(Course& course)
{
    boost::property_tree::ptree singleCoursePt;
    singleCoursePt.add(elementNameNode, course.getCourseName());
    singleCoursePt.add(elementUuidNode, course.getUuid());

    m_pt.add_child(coursesRootNode + separator + singleCourseNode, singleCoursePt);
}



