#include "persistentdatamanager.h"

PersistentDataManager::PersistentDataManager()
{
}


PersistentDataManager::~PersistentDataManager()
{
}


PersistentDataManager& PDM(void) {
    return PersistentDataManager::Instance();
}


PersistentDataManager& PersistentDataManager::Instance(void)
{
    static PersistentDataManager obj;
    return obj;
}


std::vector<boost::shared_ptr<Student> >::const_iterator PersistentDataManager::studentsBegin(void) const
{
    return m_allStudents.begin();
}


std::vector<boost::shared_ptr<Student> >::const_iterator PersistentDataManager::studentsEnd(void) const
{
    return m_allStudents.end();
}


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


std::vector<boost::shared_ptr<EvalSet> >::const_iterator PersistentDataManager::evalSetsBegin(void) const
{
    return m_allEvalSets.begin();
}


std::vector<boost::shared_ptr<EvalSet> >::const_iterator PersistentDataManager::evalSetsEnd(void) const
{
    return m_allEvalSets.end();
}


void PersistentDataManager::loadFile(std::string filename)
{
    boost::property_tree::ptree loadPt;

    if(filename.length() != 0)
    {
        boost::property_tree::xml_parser::read_xml(filename, loadPt);

        m_allCourses.clear();
        m_allGradingCriteria.clear();
        m_allStudents.clear();

        CoursesPropertyTreeParser ptreeParser;
        ptreeParser.parseTree(loadPt, std::inserter(m_allCourses, m_allCourses.begin()));

        GradingCriteriaPropertyTreeParser gcPtParser;
        gcPtParser.parseTree(loadPt, std::inserter(m_allGradingCriteria, m_allGradingCriteria.begin()));

        StudentPropertyTreeParser studentPtParser;
        studentPtParser.parseTree(loadPt,
                                  std::inserter(m_allStudents, m_allStudents.begin()),
                                  m_allCourses.begin(),
                                  m_allCourses.end(),
                                  m_allGradingCriteria.begin(),
                                  m_allGradingCriteria.end());
    }
}
