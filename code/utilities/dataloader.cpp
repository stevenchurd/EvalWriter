#include "dataloader.h"
#include "coursespropertytreeparser.h"
#include "studentpropertytreeparser.h"
#include "gradingcriteriapropertytreeparser.h"
#include "ptreeloader.h"
#include "course.h"
#include "student.h"
#include "gradingcriteria.h"

DataLoader::DataLoader(ObjectPool<Course> &coursePool,
                       ObjectPool<GradingCriteria> &gcPool,
                       ObjectPool<Student> &studentPool,
                       std::string coursesFile,
                       std::string gcFile,
                       std::string studentFile) :
    m_coursePool(coursePool), m_gcPool(gcPool), m_studentPool(studentPool),
    m_courseFile(coursesFile), m_gcFile(gcFile), m_studentFile(studentFile)
{
}


void DataLoader::loadAll(void)
{
    loadCourses();
    loadGradingCriteria();
    loadStudents();
}


void DataLoader::loadCourses(void)
{
    CoursesPropertyTreeParser ptreeParser(m_coursePool);
    PtreeLoader ptreeLoader(m_courseFile, ptreeParser);

    ptreeLoader.load();
    ptreeLoader.processTree();
}


void DataLoader::loadGradingCriteria(void)
{
    GradingCriteriaPropertyTreeParser gcPtParser(m_gcPool);
    PtreeLoader ptreeLoader2(m_gcFile, gcPtParser);

    ptreeLoader2.load();
    ptreeLoader2.processTree();
}


void DataLoader::loadStudents(void)
{
    StudentPropertyTreeParser studentPtParser(m_studentPool, m_coursePool, m_gcPool);
    PtreeLoader ptreeLoader3(m_studentFile, studentPtParser);

    ptreeLoader3.load();
    ptreeLoader3.processTree();
}
