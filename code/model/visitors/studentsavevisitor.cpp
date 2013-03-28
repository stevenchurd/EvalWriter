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
    std::list<std::string> courseNames;
    boost::property_tree::ptree newStudentNode;

    // get all the student's course names
    student.getCourseNames(inserter(courseNames, courseNames.begin()));

    newStudentNode.put(elementUuidNode, student.getUuid());
    newStudentNode.put(studentFirstNameNode, student.getFirstName());
    newStudentNode.put(studentMiddleNameNode, student.getMiddleName());
    newStudentNode.put(studentLastNameNode, student.getLastName());

    student.acceptChildren(*this);

    newStudentNode.add_child(studentCoursesNode, m_coursesPt);
    newStudentNode.add_child(studentEvalsNode, m_evalsPt);

    // add the new student to the full property tree
    m_pt.add_child(studentRootNode + separator + singleStudentNode, newStudentNode);

    m_coursesPt.clear();
    m_evalsPt.clear();
}


void StudentSaveVisitor::visit(Course& course)
{
    m_coursesPt.add(elementUuidNode, course.getUuid());
}


void StudentSaveVisitor::visit(Eval& eval)
{
    m_evalItemsPt.add(elementUuidNode, eval.getUuid());
    m_evalItemsPt.add(elementNameNode, eval.getEvalName());

    eval.acceptChildren(*this);

    m_evalsPt.add_child(singleEvalNode, m_evalItemsPt);

    m_evalItemsPt.clear();
}


void StudentSaveVisitor::visit(CriteriaItem& ci)
{
    boost::property_tree::ptree ciPt;

    ciPt.add(elementUuidNode, ci.getUuid());

    m_evalItemsPt.add_child(singleCriteriaItemNode, ciPt);
}


void StudentSaveVisitor::visit(CustomTextItem& ct)
{
    boost::property_tree::ptree ctPt;

    ctPt.add(elementUuidNode, ct.getUuid());
    ctPt.add(elementTitleNode, ct.getItemTitleStr());
    ctPt.add(elementValueNode, ct.getItemStr());

    m_evalItemsPt.add_child(customTextItemNode, ctPt);
}

