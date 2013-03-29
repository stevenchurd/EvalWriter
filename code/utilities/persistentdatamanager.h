#ifndef PERSISTENTDATAMANAGER_H
#define PERSISTENTDATAMANAGER_H

#include <vector>

#ifndef Q_MOC_RUN
#include "model/student.h"
#include "model/course.h"
#include "model/evalset.h"
#include "model/gradingcriteria.h"

#include "utilities/coursespropertytreeparser.h"
#include "utilities/gradingcriteriapropertytreeparser.h"
#include "utilities/studentpropertytreeparser.h"
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#endif



class PersistentDataManager
{
public:
    static PersistentDataManager& Instance(void);

    void loadFile(std::string filename);
    void saveFile(std::string filename) const;

    std::vector<boost::shared_ptr<Student> >::const_iterator studentsBegin(void) const;
    std::vector<boost::shared_ptr<Student> >::const_iterator studentsEnd(void) const;
    void add(boost::shared_ptr<Student> newStudent);
    void remove(std::vector<boost::shared_ptr<Student> >::const_iterator it);

    std::vector<boost::shared_ptr<Course> >::const_iterator coursesBegin(void) const;
    std::vector<boost::shared_ptr<Course> >::const_iterator coursesEnd(void) const;
    void add(boost::shared_ptr<Course> newCourse);
    void remove(std::vector<boost::shared_ptr<Course> >::const_iterator it);

    std::vector<boost::shared_ptr<GradingCriteria> >::const_iterator gradingCriteriaBegin(void) const;
    std::vector<boost::shared_ptr<GradingCriteria> >::const_iterator gradingCriteriaEnd(void) const;
    void add(boost::shared_ptr<GradingCriteria> newGradingCriteria);
    void remove(std::vector<boost::shared_ptr<GradingCriteria> >::const_iterator it);

    std::vector<boost::shared_ptr<EvalSet> >::const_iterator evalSetsBegin(void) const;
    std::vector<boost::shared_ptr<EvalSet> >::const_iterator evalSetsEnd(void) const;
    void add(boost::shared_ptr<EvalSet> newEvalSet);
    void remove(std::vector<boost::shared_ptr<EvalSet> >::const_iterator it);


private:
    PersistentDataManager();
    ~PersistentDataManager();
    PersistentDataManager(const PersistentDataManager&);
    PersistentDataManager& operator=(const PersistentDataManager&);

    std::vector<boost::shared_ptr<Student> > m_allStudents;
    std::vector<boost::shared_ptr<Course> > m_allCourses;
    std::vector<boost::shared_ptr<EvalSet> > m_allEvalSets;
    std::vector<boost::shared_ptr<GradingCriteria> > m_allGradingCriteria;


    // TODO: remove
    void createEvalSets(void);

};


template <typename T>
boost::shared_ptr<T> elementAt(typename std::vector<boost::shared_ptr<T> >::const_iterator begin, int index)
{
    boost::shared_ptr<T> elem = *(std::next(begin, index));
    return elem;
}

template <typename T>
auto iterAt(typename std::vector<boost::shared_ptr<T> >::const_iterator begin, int index) -> decltype(begin)
{
    return std::next(begin, index);
}


// shorthand function
PersistentDataManager& PDM(void);

#endif // PERSISTENTDATAMANAGER_H
