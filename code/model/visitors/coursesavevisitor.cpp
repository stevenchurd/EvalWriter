// (C) Copyright Steven Hurd 2013

#include "coursesavevisitor.h"
#include "model/course.h"
#include "xmlnodenames.h"


void CourseSaveVisitor::visit(Course& course)
{
    boost::property_tree::ptree singleCoursePt;
    singleCoursePt.add(xml_node_names::elementUuidNode, course.getUuid());
    singleCoursePt.add(xml_node_names::elementNameNode, course.getCourseName());

    m_pt.add_child(xml_node_names::coursesRootNode +
                   xml_node_names::separator +
                   xml_node_names::singleCourseNode, singleCoursePt);
}



