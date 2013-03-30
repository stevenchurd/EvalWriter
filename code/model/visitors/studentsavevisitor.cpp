// (C) Copyright Steven Hurd 2013

#include "studentsavevisitor.h"
#include <boost/foreach.hpp>
#include <list>
#include "model/student.h"
#include "model/eval.h"
#include "model/course.h"
#include "model/criteriaitem.h"
#include "model/customtextitem.h"
#include "xmlnodenames.h"


StudentSaveVisitor::StudentSaveVisitor() :
    SaveVisitor()
{
}

void StudentSaveVisitor::visit(Student& student)
{
    boost::property_tree::ptree newStudentNode;

    newStudentNode.put(xml_node_names::elementUuidNode, student.getUuid());
    newStudentNode.put(xml_node_names::studentFirstNameNode, student.getFirstName());
    newStudentNode.put(xml_node_names::studentMiddleNameNode, student.getMiddleName());
    newStudentNode.put(xml_node_names::studentLastNameNode, student.getLastName());

    student.acceptChildren(*this);

    newStudentNode.add_child(xml_node_names::studentCoursesNode, m_coursesPt);
    newStudentNode.add_child(xml_node_names::studentEvalsNode, m_evalsPt);

    // add the new student to the full property tree
    m_pt.add_child(xml_node_names::studentRootNode +
                   xml_node_names::separator +
                   xml_node_names::singleStudentNode, newStudentNode);

    m_coursesPt.clear();
    m_evalsPt.clear();
}


void StudentSaveVisitor::visit(Course& course)
{
    boost::property_tree::ptree coursePt;
    coursePt.add(xml_node_names::elementUuidNode, course.getUuid());
    m_coursesPt.add_child(xml_node_names::singleCourseNode, coursePt);
}


void StudentSaveVisitor::visit(Eval& eval)
{
    m_evalItemsPt.add(xml_node_names::elementUuidNode, eval.getUuid());
    m_evalItemsPt.add(xml_node_names::elementNameNode, eval.getEvalName());

    eval.acceptChildren(*this);

    m_evalsPt.add_child(xml_node_names::singleEvalNode, m_evalItemsPt);

    m_evalItemsPt.clear();
}


void StudentSaveVisitor::visit(CriteriaItem& ci)
{
    boost::property_tree::ptree ciPt;

    ciPt.add(xml_node_names::elementUuidNode, ci.getUuid());

    m_evalItemsPt.add_child(xml_node_names::singleCriteriaItemNode, ciPt);
}


void StudentSaveVisitor::visit(CustomTextItem& ct)
{
    boost::property_tree::ptree ctPt;

    ctPt.add(xml_node_names::elementUuidNode, ct.getUuid());
    ctPt.add(xml_node_names::elementTitleNode, ct.getItemTitleStr());
    ctPt.add(xml_node_names::elementValueNode, ct.getItemStr());

    m_evalItemsPt.add_child(xml_node_names::customTextItemNode, ctPt);
}

