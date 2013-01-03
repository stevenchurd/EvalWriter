#include "test.h"
#include "model/visitors/studentsavevisitor.h"
#include "model/visitors/coursesavevisitor.h"
#include "model/visitors/gradingcriteriasavevisitor.h"
#include "model/eval.h"
#include "model/criteriaitem.h"
#include "model/customtextitem.h"
#include "utilities/coursespropertytreeparser.h"
#include "utilities/gradingcriteriapropertytreeparser.h"
#include "utilities/studentpropertytreeparser.h"
#include "utilities/filelogger.h"
#include <boost/property_tree/xml_parser.hpp>
#include "xmlnodenames.h"

ObjectTester::ObjectTester()
{
}

void ObjectTester::runTests(void)
{

    boost::shared_ptr<Student> student(new Student("Jeff", "C", "Mexican"));
    boost::shared_ptr<Student> student2(new Student("Hairy", "J", "Houdini"));
    m_studentPool.push_back(student);
    m_studentPool.push_back(student2);

    boost::shared_ptr<Course> course(new Course("Spanish 1"));
    boost::shared_ptr<Course> course2(new Course("Spanish 2"));
    boost::shared_ptr<Course> course3(new Course("Spanish 3"));
    m_coursePool.push_back(course);
    m_coursePool.push_back(course2);
    m_coursePool.push_back(course3);

    student->addCourse(course);
    student->addCourse(course2);
    student2->addCourse(course3);


    boost::shared_ptr<CriteriaItem> ci(new CriteriaItem("ParentGradingCriteria", "Picks his nose", CriteriaItem::AVERAGE));
    boost::shared_ptr<CustomTextItem> ct(new CustomTextItem("Spends time in bathroom"));
    boost::shared_ptr<Eval> eval1 = student->addEval("Jeffs 1st semester eval");
    eval1->addEvalItem(ci);
    eval1->addEvalItem(ct);

    boost::shared_ptr<CriteriaItem> ci2(new CriteriaItem("ParentGradingCriteria", "Nose fell off", CriteriaItem::AVERAGE));
    boost::shared_ptr<CustomTextItem> ct2(new CustomTextItem("Never uses bathroom"));
    boost::shared_ptr<Eval> eval2 = student->addEval("Jeffs 2nd semester eval");
    eval2->addEvalItem(ci2);
    eval2->addEvalItem(ct2);

    StudentSaveVisitor sv;
    BOOST_FOREACH(boost::shared_ptr<Student> singleStudent, m_studentPool)
    {
        singleStudent->accept(sv);
    }
    sv.saveFile(std::string("students.xml"));

    CourseSaveVisitor csv;
    BOOST_FOREACH(boost::shared_ptr<Course> singleCourse, m_coursePool)
    {
        singleCourse->accept(csv);
    }
    csv.saveFile(std::string("courses.xml"));



}


void ObjectTester::runGradingCriteriaTests(void)
{
    boost::shared_ptr<GradingCriteria> gc(new GradingCriteria("Nose picking ability")) ;
    gc->addCriteriaItem("Average at picking his nose", CriteriaItem::AVERAGE);
    gc->addCriteriaItem("Below average at picking his nose", CriteriaItem::BELOW_AVERAGE);
    gc->addCriteriaItem("Excellent at picking his nose", CriteriaItem::EXCELLENT);
    gc->addCriteriaItem("Poor at picking his nose", CriteriaItem::POOR);
    gc->addCriteriaItem("Good at picking his nose", CriteriaItem::GOOD);

    m_gradingCriteria.push_back(gc);

    boost::shared_ptr<GradingCriteria> gc2(new GradingCriteria("Butt picking ability")) ;
    gc2->addCriteriaItem("Average at picking his butt", CriteriaItem::AVERAGE);
    gc2->addCriteriaItem("Below average at picking his butt", CriteriaItem::BELOW_AVERAGE);
    gc2->addCriteriaItem("Excellent at picking his butt", CriteriaItem::EXCELLENT);
    gc2->addCriteriaItem("Poor at picking his butt", CriteriaItem::POOR);
    gc2->addCriteriaItem("Good at picking his butt", CriteriaItem::GOOD);

    m_gradingCriteria.push_back(gc2);


    GradingCriteriaSaveVisitor gcv;
    BOOST_FOREACH(boost::shared_ptr<GradingCriteria> singleGradingCriteria, m_gradingCriteria)
    {
        singleGradingCriteria->accept(gcv);
    }
    gcv.saveFile(std::string("gradingCriteria.xml"));
}


void ObjectTester::runLoadTests(void)
{
    std::ofstream file;

    file.open("test-out.xml");

    boost::property_tree::ptree coursesPt;
    boost::property_tree::ptree gcsPt;
    boost::property_tree::ptree studentsPt;
    boost::property_tree::ptree testPt;

    boost::property_tree::xml_parser::read_xml("test.xml", testPt);
#if 0
    boost::property_tree::xml_parser::read_xml("courses.xml", coursesPt);
    boost::property_tree::xml_parser::read_xml("gradingCriteria.xml", gcsPt);
    boost::property_tree::xml_parser::read_xml("students.xml", studentsPt);
#endif

    coursesPt = testPt;
    studentsPt = testPt;
    gcsPt = testPt;

    CoursesPropertyTreeParser ptreeParser;
    ptreeParser.parseTree(coursesPt, std::inserter(m_coursePool, m_coursePool.begin()));

    CourseSaveVisitor csv2;
    BOOST_FOREACH(boost::shared_ptr<Course> singleCourse, m_coursePool)
    {
        singleCourse->accept(csv2);
    }
    csv2.saveFile(file);


    GradingCriteriaPropertyTreeParser gcPtParser;
    gcPtParser.parseTree(gcsPt, std::inserter(m_gradingCriteria, m_gradingCriteria.begin()));

    GradingCriteriaSaveVisitor gcsv;
    BOOST_FOREACH(boost::shared_ptr<GradingCriteria> singleGradingCriteria, m_gradingCriteria)
    {
        singleGradingCriteria->accept(gcsv);
    }
    gcsv.saveFile(file);


    StudentPropertyTreeParser studentPtParser;
    studentPtParser.parseTree(studentsPt,
                              std::inserter(m_studentPool, m_studentPool.begin()),
                              m_coursePool.begin(),
                              m_coursePool.end(),
                              m_gradingCriteria.begin(),
                              m_gradingCriteria.end());

    StudentSaveVisitor ssv;
    BOOST_FOREACH(boost::shared_ptr<Student> singleStudent, m_studentPool)
    {
        singleStudent->accept(ssv);
    }
    ssv.saveFile(file);

    file.close();
}


