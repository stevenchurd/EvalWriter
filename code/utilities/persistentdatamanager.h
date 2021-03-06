#ifndef PERSISTENTDATAMANAGER_H
#define PERSISTENTDATAMANAGER_H

#include <vector>
#include <unordered_map>
#include <QObject>

#include "evalexceptions.h"

#ifndef Q_MOC_RUN
#include "boost/any.hpp"
#include "model/student.h"
#include "model/course.h"
#include "model/evalset.h"
#include "model/gradingcriteria.h"
#endif



class PersistentDataManager : public QObject
{
    Q_OBJECT

public:
    static PersistentDataManager& Instance(void);

    static const std::string s_saveFileName;
    static const std::string s_crashFileName;
    static const std::string s_initialWriteFileName;
    static const std::string s_lastReadFileName;

    void loadFile(std::string filename);
    void saveFile(std::string filename, bool crashfile = false);

    std::vector<boost::shared_ptr<Student> >::const_iterator studentsBegin(void) const;
    std::vector<boost::shared_ptr<Student> >::const_iterator studentsEnd(void) const;
    unsigned int add(boost::shared_ptr<Student> newStudent);
    void remove(std::vector<boost::shared_ptr<Student> >::const_iterator it);

    std::vector<boost::shared_ptr<Course> >::const_iterator coursesBegin(void) const;
    std::vector<boost::shared_ptr<Course> >::const_iterator coursesEnd(void) const;
    unsigned int add(boost::shared_ptr<Course> newCourse);
    void remove(std::vector<boost::shared_ptr<Course> >::const_iterator it);

    std::vector<boost::shared_ptr<GradingCriteria> >::const_iterator gradingCriteriaBegin(void) const;
    std::vector<boost::shared_ptr<GradingCriteria> >::const_iterator gradingCriteriaEnd(void) const;
    unsigned int add(boost::shared_ptr<GradingCriteria> newGradingCriteria);
    void remove(std::vector<boost::shared_ptr<GradingCriteria> >::const_iterator it);

    std::vector<boost::shared_ptr<EvalSet> >::const_iterator evalSetsBegin(void) const;
    std::vector<boost::shared_ptr<EvalSet> >::const_iterator evalSetsEnd(void) const;
    unsigned int add(boost::shared_ptr<EvalSet> newEvalSet);
    void remove(std::vector<boost::shared_ptr<EvalSet> >::const_iterator it);

    template <typename T>
    bool getItemByUuid(std::string uuid, boost::shared_ptr<T>& item);

signals:
    void courseDataChanged(std::string uuid);
    void studentDataChanged(std::string uuid);
    void evalSetDataChanged(std::string uuid);
    void evalDataChanged(std::string uuid);

private:
    PersistentDataManager();
    ~PersistentDataManager();
    PersistentDataManager(const PersistentDataManager&);
    PersistentDataManager& operator=(const PersistentDataManager&);

    template <typename T, typename C>
    int add(T& item, C& container);

    const static std::string s_savepath;

    std::vector<boost::shared_ptr<Student> > m_allStudents;
    std::vector<boost::shared_ptr<Course> > m_allCourses;
    std::vector<boost::shared_ptr<EvalSet> > m_allEvalSets;
    std::vector<boost::shared_ptr<GradingCriteria> > m_allGradingCriteria;

    void setupUuidMap(void);

    std::unordered_map<std::string, boost::any> m_uuidMap;
};


template <typename T>
bool PersistentDataManager::getItemByUuid(std::string uuid, boost::shared_ptr<T>& item)
{
    auto it = m_uuidMap.find(uuid);

    if(it != m_uuidMap.end())
    {
        // first see if it's of the same type
        if(it->second.type() != typeid(item))
        {
            return false;
        }

        try {
            item = boost::any_cast<boost::shared_ptr<T> >(it->second);
        } catch(boost::bad_any_cast&) {
            return false;
        }
    }
    else
    {
        // if the item wasn't found, attempt to rebuild the map since we don't
        // update after every item add
        setupUuidMap();

        it = m_uuidMap.find(uuid);

        if(it != m_uuidMap.end())
        {
            try {
                item = boost::any_cast<boost::shared_ptr<T> >(it->second);
            } catch(boost::bad_any_cast&) {
                return false;
            }
        }
        else
        {
            // there should never be an item not in the map
            assert(false);
            throw ItemNotFoundException(std::string("Item not found with UUID: " + uuid));
        }
    }

    return true;
}


template <typename T, typename C>
int PersistentDataManager::add(T& newItem, C& container)
{
    auto it = std::find_if(container.begin(), container.end(),
                           [&newItem] (T item)
                           { return (newItem < item); });

    unsigned int row = std::distance(container.begin(), it);
    container.insert(it, newItem);
    m_uuidMap.insert(std::make_pair<std::string, boost::any>(
                         newItem->getUuid(), newItem));
    return row;
}


template <typename T, typename C>
int insertLocation(T& newItem, C& containerBegin, C& containerEnd)
{
    auto it = std::find_if(containerBegin, containerEnd,
                           [&newItem] (T item)
                           { return (newItem < item); });

    unsigned int row = std::distance(containerBegin, it);
    return row;
}


//
// Non-class, non-friend helper functions
//
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

boost::shared_ptr<Student> getNthStudentInCourse(unsigned int n, boost::shared_ptr<Course> course);

// shorthand function
PersistentDataManager& PDM(void);

#endif // PERSISTENTDATAMANAGER_H
