// (C) Copyright Steven Hurd 2013

#ifndef STUDENTPROPERTYTREEPARSER_H
#define STUDENTPROPERTYTREEPARSER_H

#include <boost/property_tree/ptree.hpp>
#include <boost/foreach.hpp>
#include <list>
#include "model/gradingcriteria.h"
#include "model/course.h"
#include "model/eval.h"

class Eval;
class Student;
class Course;


class StudentPropertyTreeParser
{
public:
    StudentPropertyTreeParser::StudentPropertyTreeParser() {}
    virtual ~StudentPropertyTreeParser() {}

    template <typename OutputIterator, typename InputIterator1, typename InputIterator2>
    void parseTree(boost::property_tree::ptree& pt,
                   OutputIterator& dest,
                   InputIterator1 courseIterFirst,
                   InputIterator1 courseIterLast,
                   InputIterator2 gcIterFirst,
                   InputIterator2 gcIterLast);

private:
    template <typename OutputIterator, typename InputIterator1, typename InputIterator2>
    void parseStudentNode(boost::property_tree::ptree& pt,
                          OutputIterator& dest,
                          InputIterator1& courseIterFirst,
                          InputIterator1& courseIterLast,
                          InputIterator2& gcIterFirst,
                          InputIterator2& gcIterLast);

    template <typename InputIterator>
    void parseEvalNode(boost::property_tree::ptree& pt,
                       boost::shared_ptr<Student>& student,
                       InputIterator& gcIterFirst,
                       InputIterator& gcIterLast);

    template <typename InputIterator>
    void parseCourseNode(boost::property_tree::ptree& pt,
                         boost::shared_ptr<Student>& student,
                         InputIterator& courseIterFirst,
                         InputIterator& courseIterLast);

    template <typename InputIterator>
    void parseEvalItemNode(boost::property_tree::ptree& pt,
                           std::string ptName,
                           boost::shared_ptr<Eval> &eval,
                           InputIterator& gcIterFirst,
                           InputIterator& gcIterLast);

    template <typename InputIterator>
    void parseCriteriaItemNode(
            boost::property_tree::ptree& pt,
            boost::shared_ptr<Eval>& eval,
            InputIterator& gcIterFirst,
            InputIterator& gcIterLast);

    void parseCustomTextNode(boost::property_tree::ptree& pt,
                             boost::shared_ptr<Eval>& eval);


};


template <typename OutputIterator, typename InputIterator1, typename InputIterator2>
void StudentPropertyTreeParser::parseTree(
        boost::property_tree::ptree& pt,
        OutputIterator& studentsDest,
        InputIterator1 courseIterFirst,
        InputIterator1 courseIterLast,
        InputIterator2 gcIterFirst,
        InputIterator2 gcIterLast)
{
    BOOST_FOREACH(const boost::property_tree::ptree::value_type &v,
                  pt.get_child(studentRootNode)) {
        // v.first is the name of the child.
        if(v.first != singleStudentNode)
        {
            throw InvalidXmlException(
                        std::string("Expected student node: ") + v.first);
        }

        // v.second is the child tree.
        boost::property_tree::ptree studentPt = v.second;
        parseStudentNode(studentPt,
                         studentsDest,
                         courseIterFirst,
                         courseIterLast,
                         gcIterFirst,
                         gcIterLast);
    }
}


template <typename OutputIterator, typename InputIterator1, typename InputIterator2>
void StudentPropertyTreeParser::parseStudentNode(
        boost::property_tree::ptree& pt,
        OutputIterator& studentsDest,
        InputIterator1& courseIterFirst,
        InputIterator1& courseIterLast,
        InputIterator2& gcIterFirst,
        InputIterator2& gcIterLast)
{
    std::string firstName;
    std::string middleName;
    std::string lastName;

    try{
        firstName = pt.get<std::string>(studentFirstNameNode);
        middleName = pt.get<std::string>(studentMiddleNameNode);
        lastName = pt.get<std::string>(studentLastNameNode);
    } catch(boost::property_tree::ptree_error& pte) {
        throw InvalidXmlException(
                    std::string("No name element found: ") + pte.what());
    }

    boost::shared_ptr<Student> student(new Student(firstName, middleName, lastName));

    for (boost::property_tree::ptree::const_iterator it = pt.begin(); it != pt.end(); ++it)
    {
        if(it->first == studentCoursesNode)
        {
            boost::property_tree::ptree courseNode = it->second;
            parseCourseNode(courseNode, student, courseIterFirst, courseIterLast);
        }
        else if(it->first == studentEvalsNode)
        {
            boost::property_tree::ptree evalNode = it->second;
            parseEvalNode(evalNode, student, gcIterFirst, gcIterLast);
        }
        else if(it->first == studentFirstNameNode ||
                it->first == studentMiddleNameNode ||
                it->first == studentLastNameNode)
        {
            // don't need to do anything, these were already extracted
        }
        else
        {
            throw InvalidXmlException("Invalid XML node found in student: " + it->first);
        }
    }

    studentsDest++ = student;
}


template <typename InputIterator>
void StudentPropertyTreeParser::parseCourseNode(boost::property_tree::ptree& pt,
                     boost::shared_ptr<Student>& student,
                     InputIterator& courseIterFirst,
                     InputIterator& courseIterLast)
{
    for (boost::property_tree::ptree::const_iterator it = pt.begin(); it != pt.end(); ++it)
    {
        // first see if the course exists in the course pool
        // if it doesn't, throw an exception...this course shouldn't be here
        std::list<boost::shared_ptr<Course> > courses;
        InputIterator courseIt = std::find_if(courseIterFirst,
                                              courseIterLast,
                                              hasCourseName(it->second.data()));

        while(courseIt != courseIterLast)
        {
            courses.push_back(*courseIt);
            courseIt = std::find_if(++courseIt,
                                    courseIterLast,
                                    hasCourseName(it->second.data()));
        }

        if(courses.size() != 1)
        {
            std::ostringstream numCourses;
            numCourses << courses.size();

            // if there's not exactly one item in the list at the end,
            // something went wrong
            throw InvalidXmlException(std::string("Course (")
                                      + std::string(it->second.data())
                                      + std::string(") was found this many times: ")
                                      + numCourses.str());
        }

        student->addCourse(courses.front());
    }
}


template <typename InputIterator>
void StudentPropertyTreeParser::parseCriteriaItemNode(
        boost::property_tree::ptree& pt,
        boost::shared_ptr<Eval>& eval,
        InputIterator& gcIterFirst,
        InputIterator& gcIterLast)
{
    std::string itemName;
    std::string itemParent;
    CriteriaItem::CriteriaItemLevelType itemLevel;

    try {
        itemName = pt.get<std::string>(elementValueNode);
        itemParent = pt.get<std::string>(criteriaItemParentItemNode);
        itemLevel = static_cast<CriteriaItem::CriteriaItemLevelType>(
                    pt.get<unsigned int>(criteriaItemLevelNode));
    } catch(boost::property_tree::ptree_error& pte) {
        throw InvalidXmlException(
                    std::string("Node not found: ") + pte.what());
    }

    std::list<boost::shared_ptr<GradingCriteria> > gradingCriterias;
    InputIterator gcIter = std::find_if(gcIterFirst, gcIterLast, hasGradingCriteriaItem(itemParent));
    while(gcIter != gcIterLast)
    {
        gradingCriterias.push_back(*gcIter);
        gcIter = std::find_if(++gcIter,
                              gcIterLast,
                              hasGradingCriteriaItem(itemParent));
    }

    if(gradingCriterias.size() != 1)
    {
        std::ostringstream numGc;
        numGc << gradingCriterias.size();

        // if there's not exactly one item in the list at the end,
        // something went wrong
        throw InvalidXmlException(std::string("Grading criteria(")
                                  + itemParent
                                  + std::string(") was found this many times: ")
                                  + numGc.str());
    }

    boost::shared_ptr<CriteriaItem> ci =
            gradingCriterias.front()->getCriteriaItem(
                itemName,
                itemLevel);

    eval->addEvalItem(ci);
}


template <typename InputIterator>
void StudentPropertyTreeParser::parseEvalItemNode(
        boost::property_tree::ptree& pt,
        std::string ptName,
        boost::shared_ptr<Eval>& eval,
        InputIterator& gcIterFirst,
        InputIterator& gcIterLast)
{
    if(ptName == singleCriteriaItemNode)
    {
        parseCriteriaItemNode(pt, eval, gcIterFirst, gcIterLast);
    }
    else if(ptName == customTextItemNode)
    {
        parseCustomTextNode(pt, eval);
    }
    else if(ptName == elementNameNode)
    {
        // name already extracted so nothing necessary to do
    }
    else
    {
        throw InvalidXmlException("Invalid node found in Eval tree: " + ptName);
    }
}


template <typename InputIterator>
void StudentPropertyTreeParser::parseEvalNode(
        boost::property_tree::ptree& pt,
        boost::shared_ptr<Student>& student,
        InputIterator& gcIterFirst,
        InputIterator& gcIterLast)
{
    for (boost::property_tree::ptree::const_iterator it = pt.begin(); it != pt.end(); ++it)
    {
        std::string evalName;

        try{
            evalName = it->second.get<std::string>(elementNameNode);
        } catch(boost::property_tree::ptree_error& pte) {
            throw InvalidXmlException(
                        std::string("No name element found: ") + pte.what());
        }

        boost::shared_ptr<Eval> newEval = student->addEval(evalName);

        // now iterate through this whole node and construct all the elements
        for(boost::property_tree::ptree::const_iterator critIt = it->second.begin(); critIt != it->second.end(); ++critIt)
        {
            boost::property_tree::ptree criteriaPt = critIt->second;
            parseEvalItemNode(criteriaPt, critIt->first, newEval, gcIterFirst, gcIterLast);
        }
    }
}



#endif // STUDENTPROPERTYTREEPARSER_H
