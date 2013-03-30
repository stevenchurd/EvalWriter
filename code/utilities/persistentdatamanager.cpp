#include "persistentdatamanager.h"
#include "model/visitors/coursesavevisitor.h"
#include "model/visitors/studentsavevisitor.h"
#include "model/visitors/gradingcriteriasavevisitor.h"
#include "model/visitors/evalsetsavevisitor.h"

#include "utilities/coursespropertytreeparser.h"
#include "utilities/gradingcriteriapropertytreeparser.h"
#include "utilities/studentpropertytreeparser.h"
#include "utilities/evalsetpropertytreeparser.h"
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>

PersistentDataManager::PersistentDataManager()
{
}


PersistentDataManager::~PersistentDataManager()
{
    try
    {
        saveFile("../testfiles/test7.ewd");
    }
    catch(...)
    {
        // do nothing...destructors don't throw
    }
}


PersistentDataManager& PDM(void) {
    return PersistentDataManager::Instance();
}


PersistentDataManager& PersistentDataManager::Instance(void)
{
    static PersistentDataManager obj;
    return obj;
}




//
// Student functions
//
std::vector<boost::shared_ptr<Student> >::const_iterator PersistentDataManager::studentsBegin(void) const
{
    return m_allStudents.begin();
}


std::vector<boost::shared_ptr<Student> >::const_iterator PersistentDataManager::studentsEnd(void) const
{
    return m_allStudents.end();
}



//
// Course functions
//
std::vector<boost::shared_ptr<Course> >::const_iterator PersistentDataManager::coursesBegin(void) const
{
    return m_allCourses.begin();
}


std::vector<boost::shared_ptr<Course> >::const_iterator PersistentDataManager::coursesEnd(void) const
{
    return m_allCourses.end();
}


void PersistentDataManager::add(boost::shared_ptr<Course> newCourse)
{
    m_allCourses.push_back(newCourse);
}


void PersistentDataManager::remove(std::vector<boost::shared_ptr<Course> >::const_iterator it)
{
    m_allCourses.erase(it);
}




//
// Grading Criteria function
//
std::vector<boost::shared_ptr<GradingCriteria> >::const_iterator PersistentDataManager::gradingCriteriaBegin(void) const
{
    return m_allGradingCriteria.begin();
}


std::vector<boost::shared_ptr<GradingCriteria> >::const_iterator PersistentDataManager::gradingCriteriaEnd(void) const
{
    return m_allGradingCriteria.end();
}


void PersistentDataManager::remove(std::vector<boost::shared_ptr<GradingCriteria> >::const_iterator it)
{
    m_allGradingCriteria.erase(it);
}




//
// Eval Set functions
//
std::vector<boost::shared_ptr<EvalSet> >::const_iterator PersistentDataManager::evalSetsBegin(void) const
{
    return m_allEvalSets.begin();
}


std::vector<boost::shared_ptr<EvalSet> >::const_iterator PersistentDataManager::evalSetsEnd(void) const
{
    return m_allEvalSets.end();
}


void PersistentDataManager::add(boost::shared_ptr<EvalSet> newEvalSet)
{
    m_allEvalSets.push_back(newEvalSet);
}


void PersistentDataManager::remove(std::vector<boost::shared_ptr<EvalSet> >::const_iterator it)
{
    m_allEvalSets.erase(it);
}



//
// Load and save functions
//

void PersistentDataManager::loadFile(std::string filename)
{
    boost::property_tree::ptree loadPt;

    if(filename.length() != 0)
    {
        boost::property_tree::xml_parser::read_xml(filename, loadPt);

        m_allCourses.clear();
        m_allGradingCriteria.clear();
        m_allStudents.clear();
        m_allEvalSets.clear();

        CoursesPropertyTreeParser ptreeParser;
        ptreeParser.parseTree(loadPt, std::inserter(m_allCourses, m_allCourses.begin()));

        GradingCriteriaPropertyTreeParser gcPtParser;
        gcPtParser.parseTree(loadPt, std::inserter(m_allGradingCriteria, m_allGradingCriteria.begin()));

        StudentPropertyTreeParser studentPtParser;
        studentPtParser.parseTree(loadPt,
                                  std::inserter(m_allStudents, m_allStudents.begin()),
                                  m_allCourses.cbegin(),
                                  m_allCourses.cend(),
                                  m_allGradingCriteria.cbegin(),
                                  m_allGradingCriteria.cend());

        EvalSetPropertyTreeParser evalSetPtParser;
        evalSetPtParser.parseTree(loadPt,
                                  std::inserter(m_allEvalSets, m_allEvalSets.begin()),
                                  m_allStudents.cbegin(),
                                  m_allStudents.cend());
    }
}


void PersistentDataManager::saveFile(std::string filename) const
{
    std::ofstream file;

    if(filename.size() != 0)
    {
        file.open(filename);

        CourseSaveVisitor csv;
        std::for_each(m_allCourses.begin(), m_allCourses.end(),
                      [&csv] (boost::shared_ptr<Course> singleCourse)
        {
            singleCourse->accept(csv);
        });
        csv.saveFile(file);

        GradingCriteriaSaveVisitor gcsv;
        std::for_each(m_allGradingCriteria.begin(), m_allGradingCriteria.end(),
                      [&gcsv] (boost::shared_ptr<GradingCriteria> singleGradingCriteria)
        {
            singleGradingCriteria->accept(gcsv);
        });
        gcsv.saveFile(file);

        StudentSaveVisitor ssv;
        std::for_each(m_allStudents.begin(), m_allStudents.end(),
                      [&ssv] (boost::shared_ptr<Student> singleStudent)
        {
            singleStudent->accept(ssv);
        });
        ssv.saveFile(file);

        EvalSetSaveVisitor esv;
        std::for_each(m_allEvalSets.begin(), m_allEvalSets.end(),
                      [&esv] (boost::shared_ptr<EvalSet> singleEvalSet)
        {
            singleEvalSet->accept(esv);
        });
        esv.saveFile(file);

        file.close();
    }
}
