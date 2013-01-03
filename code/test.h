#ifndef TEST_H
#define TEST_H

#include <QList>
#include "model/student.h"
#include "model/course.h"
#include "model/gradingcriteria.h"

class ObjectTester
{
public:
    ObjectTester();
    void runTests(void);
    void runGradingCriteriaTests(void);
    void runLoadTests(void);

private:

    QList<boost::shared_ptr<Student> > m_studentPool;
    QList<boost::shared_ptr<Course> > m_coursePool;
    QList<boost::shared_ptr<GradingCriteria> > m_gradingCriteria;

};

#endif // TEST_H
