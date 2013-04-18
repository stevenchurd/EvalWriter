#include "persistentdatamanager.h"
#include "model/visitors/coursesavevisitor.h"
#include "model/visitors/studentsavevisitor.h"
#include "model/visitors/gradingcriteriasavevisitor.h"
#include "model/visitors/evalsetsavevisitor.h"
#include "model/visitors/removeevalvisitor.h"
#include "model/visitors/containerinsertvisitor.h"

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
    return m_allStudents.cbegin();
}


std::vector<boost::shared_ptr<Student> >::const_iterator PersistentDataManager::studentsEnd(void) const
{
    return m_allStudents.cend();
}


void PersistentDataManager::add(boost::shared_ptr<Student> newStudent)
{
    m_allStudents.push_back(newStudent);
    m_uuidMap.insert(std::make_pair<std::string, boost::any>(
                         newStudent->getUuid(), newStudent));
}


void PersistentDataManager::remove(std::vector<boost::shared_ptr<Student> >::const_iterator it)
{
    // if we are removing a student, we need to make sure all their owned Evals are removed
    // from eval sets prior to removing the student
    boost::shared_ptr<Student> student = *it;
    std::vector<std::string> uuids;

    // get all the UUIDs of the evals owned by the student
    std::for_each(student->evalsBegin(), student->evalsEnd(),
                  [&uuids] (boost::shared_ptr<Eval> eval)
    {
        uuids.push_back(eval->getUuid());
    });

    RemoveEvalVisitor rev(uuids);

    std::for_each(m_allEvalSets.begin(), m_allEvalSets.end(),
                  [&rev] (boost::shared_ptr<EvalSet> evalSet)
    {
        evalSet->accept(rev);
    });

    m_allStudents.erase(it);
}




//
// Course functions
//
std::vector<boost::shared_ptr<Course> >::const_iterator PersistentDataManager::coursesBegin(void) const
{
    return m_allCourses.cbegin();
}


std::vector<boost::shared_ptr<Course> >::const_iterator PersistentDataManager::coursesEnd(void) const
{
    return m_allCourses.cend();
}


void PersistentDataManager::add(boost::shared_ptr<Course> newCourse)
{
    m_allCourses.push_back(newCourse);
    m_uuidMap.insert(std::make_pair<std::string, boost::any>(
                         newCourse->getUuid(), newCourse));
}


void PersistentDataManager::remove(std::vector<boost::shared_ptr<Course> >::const_iterator it)
{
    // if we're removing a course from the main list, we also need to remove it
    // from any students who are in this course
    boost::shared_ptr<Course> course = *it;
    std::for_each(studentsBegin(), studentsEnd(),
                  [&course] (boost::shared_ptr<Student> student)
    {
        student->removeCourse(course->getUuid());
    });

    m_allCourses.erase(it);
}




//
// Grading Criteria function
//
std::vector<boost::shared_ptr<GradingCriteria> >::const_iterator PersistentDataManager::gradingCriteriaBegin(void) const
{
    return m_allGradingCriteria.cbegin();
}


std::vector<boost::shared_ptr<GradingCriteria> >::const_iterator PersistentDataManager::gradingCriteriaEnd(void) const
{
    return m_allGradingCriteria.cend();
}


void PersistentDataManager::add(boost::shared_ptr<GradingCriteria> newGradingCriteria)
{
    m_allGradingCriteria.push_back(newGradingCriteria);
    m_uuidMap.insert(std::make_pair<std::string, boost::any>(
                         newGradingCriteria->getUuid(), newGradingCriteria));
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
    return m_allEvalSets.cbegin();
}


std::vector<boost::shared_ptr<EvalSet> >::const_iterator PersistentDataManager::evalSetsEnd(void) const
{
    return m_allEvalSets.cend();
}


void PersistentDataManager::add(boost::shared_ptr<EvalSet> newEvalSet)
{
    m_allEvalSets.push_back(newEvalSet);
    m_uuidMap.insert(std::make_pair<std::string, boost::any>(
                         newEvalSet->getUuid(), newEvalSet));
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


    // set up the Uuid map after loading the data
    setupUuidMap();
}


void PersistentDataManager::setupUuidMap(void)
{
    ContainerInsertVisitor<decltype(m_uuidMap)> civ(m_uuidMap);

    m_uuidMap.clear();

    std::for_each(m_allEvalSets.begin(), m_allEvalSets.end(),
                  [&civ, this] (boost::shared_ptr<EvalSet> evalSet)
    {
        evalSet->accept(civ);
        m_uuidMap.insert(std::make_pair<std::string, boost::any>(evalSet->getUuid(), evalSet));
    });

    std::for_each(m_allCourses.begin(), m_allCourses.end(),
                  [&civ, this] (boost::shared_ptr<Course> course)
    {
        m_uuidMap.insert(std::make_pair<std::string, boost::any>(course->getUuid(), course));
    });

    std::for_each(m_allStudents.begin(), m_allStudents.end(),
                  [&civ, this] (boost::shared_ptr<Student> student)
    {
        m_uuidMap.insert(std::make_pair<std::string, boost::any>(student->getUuid(), student));
    });

    std::for_each(m_allGradingCriteria.begin(), m_allGradingCriteria.end(),
                  [&civ, this] (boost::shared_ptr<GradingCriteria> gc)
    {
        gc->accept(civ);
        m_uuidMap.insert(std::make_pair<std::string, boost::any>(gc->getUuid(), gc));
    });

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


boost::shared_ptr<Student> getNthStudentInCourse(unsigned int n, boost::shared_ptr<Course> course)
{
    unsigned int i=0;
    boost::shared_ptr<Student> student;

    auto it = std::find_if(PDM().studentsBegin(), PDM().studentsEnd(),
                  [&n, &i, course] (boost::shared_ptr<Student> vectStudent)->bool
    {
        if(vectStudent->isInCourse(course))
        {
            i++;
            return i-1 == n;
        }

        return false;
    });

    if(it != PDM().studentsEnd())
    {
        student = *it;
    }

    return student;
}
