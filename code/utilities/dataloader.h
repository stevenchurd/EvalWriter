#ifndef DATALOADER_H
#define DATALOADER_H

//TODO: remove

#if 0
#include <string>

//forward declarations

template <typename T>
class ObjectPool;

class Course;
class GradingCriteria;
class Student;

class DataLoader
{
public:
    DataLoader(ObjectPool<Course>& coursePool,
               ObjectPool<GradingCriteria>& gcPool,
               ObjectPool<Student>& studentPool,
               std::string coursesFile,
               std::string gcFile,
               std::string studentFile);

    virtual ~DataLoader() {}

    void loadAll(void);
    void loadCourses(void);
    void loadGradingCriteria(void);
    void loadStudents(void);

private:
    ObjectPool<Course>& m_coursePool;
    ObjectPool<GradingCriteria>& m_gcPool;
    ObjectPool<Student>& m_studentPool;

    std::string m_courseFile;
    std::string m_gcFile;
    std::string m_studentFile;
};

#endif // DATALOADER_H
#endif
