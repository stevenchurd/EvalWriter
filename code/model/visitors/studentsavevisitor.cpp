
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
    m_coursesPt.add(singleCourseNode, course.getCourseName());
}


void StudentSaveVisitor::visit(Eval& eval)
{
    m_evalItemsPt.add(elementNameNode, eval.getEvalName());

    eval.acceptChildren(*this);

    m_evalsPt.add_child(singleEvalNode, m_evalItemsPt);

    m_evalItemsPt.clear();
}


void StudentSaveVisitor::visit(CriteriaItem& ci)
{
    m_evalItemsPt.add(singleCriteriaItemNode + separator + elementValueNode, ci.getItemStr());
    m_evalItemsPt.add(singleCriteriaItemNode + separator + criteriaItemParentItemNode, ci.getParentCriteriaName());
    m_evalItemsPt.add(singleCriteriaItemNode + separator + criteriaItemLevelNode, ci.getCriteriaItemLevel());
}


void StudentSaveVisitor::visit(CustomTextItem& ct)
{
    m_evalItemsPt.add(customTextItemNode + separator + elementValueNode, ct.getItemStr());
}

