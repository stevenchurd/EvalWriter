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
    // if the tree is empty, just return
    if(pt.empty() || pt.get_child_optional(xml_node_names::studentRootNode) == nullptr)
    {
        return;
    }

    BOOST_FOREACH(const boost::property_tree::ptree::value_type &v,
                  pt.get_child(xml_node_names::studentRootNode))
    {
        // v.first is the name of the child.
        if(v.first != xml_node_names::singleStudentNode)
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
    Student::Gender gender;
    boost::uuids::uuid studentUuid;
    boost::uuids::string_generator gen;

    try{
        firstName = pt.get<std::string>(xml_node_names::studentFirstNameNode);
        middleName = pt.get<std::string>(xml_node_names::studentMiddleNameNode);
        lastName = pt.get<std::string>(xml_node_names::studentLastNameNode);
        gender = static_cast<Student::Gender>(pt.get<int>(xml_node_names::studentGenderNode));
        studentUuid = gen(pt.get<std::string>(xml_node_names::elementUuidNode));
    } catch(boost::property_tree::ptree_error& pte) {
        throw InvalidXmlException(
                    std::string("No name element found: ") + pte.what());
    }

    boost::shared_ptr<Student> student(new Student(firstName, middleName, lastName,
                                                   gender, studentUuid));

    for (boost::property_tree::ptree::const_iterator it = pt.begin(); it != pt.end(); ++it)
    {
        if(it->first == xml_node_names::studentCoursesNode)
        {
            boost::property_tree::ptree courseNode = it->second;
            parseCourseNode(courseNode, student, courseIterFirst, courseIterLast);
        }
        else if(it->first == xml_node_names::studentEvalsNode)
        {
            boost::property_tree::ptree evalNode = it->second;
            parseEvalNode(evalNode, student, gcIterFirst, gcIterLast);
        }
        else if(it->first == xml_node_names::studentFirstNameNode ||
                it->first == xml_node_names::studentMiddleNameNode ||
                it->first == xml_node_names::studentLastNameNode ||
                it->first == xml_node_names::studentGenderNode ||
                it->first == xml_node_names::elementUuidNode)
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
        if(it->first != xml_node_names::singleCourseNode)
        {
            throw InvalidXmlException(
                        std::string("Expected course node: ") + it->first);
        }

        boost::uuids::uuid courseUuid;
        boost::uuids::string_generator gen;

        try {
            courseUuid = gen(it->second.get<std::string>(xml_node_names::elementUuidNode));
        } catch(boost::property_tree::ptree_error& pte) {
            throw InvalidXmlException(
                        std::string("Element not found: ") + pte.what());
        }

        // now that we have the UUID, search the courses to make sure it exists
        // before adding it to the student

        InputIterator foundCourse =
                std::find_if(courseIterFirst, courseIterLast,
                             [&courseUuid] (boost::shared_ptr<Course> course)
                { return course->getUuid() == to_string(courseUuid); });

        if(foundCourse == courseIterLast)
        {
            throw InvalidXmlException(
                        std::string("Course not found in course list: ") + to_string(courseUuid));
        }

        student->addCourse(*foundCourse);
    }
}


template <typename InputIterator>
void StudentPropertyTreeParser::parseCriteriaItemNode(
        boost::property_tree::ptree& pt,
        boost::shared_ptr<Eval>& eval,
        InputIterator& gcIterFirst,
        InputIterator& gcIterLast)
{
    boost::uuids::uuid ciUuid;
    boost::uuids::string_generator gen;

    try {
        ciUuid = gen(pt.get<std::string>(xml_node_names::elementUuidNode));
    } catch(boost::property_tree::ptree_error& pte) {
        throw InvalidXmlException(
                    std::string("Element not found: ") + pte.what());
    }

    // now loop through the the GradingCriteria items until they find a match
    // for this criteriaItem uuid
    boost::shared_ptr<CriteriaItem> ci;
    std::find_if(gcIterFirst, gcIterLast,
                 [&ci, &ciUuid] (boost::shared_ptr<GradingCriteria> singleGradingCriteria)
                 { return singleGradingCriteria->getCriteriaItemById(to_string(ciUuid), ci); });

    // if the item wasn't found, something is wrong in the XML
    if(ci == nullptr)
    {
        throw InvalidXmlException(
                    std::string("Element not found: ") + to_string(ciUuid));
    }

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
    if(ptName == xml_node_names::singleCriteriaItemNode)
    {
        parseCriteriaItemNode(pt, eval, gcIterFirst, gcIterLast);
    }
    else if(ptName == xml_node_names::customTextItemNode)
    {
        parseCustomTextNode(pt, eval);
    }
    else if(ptName == xml_node_names::elementNameNode ||
            ptName == xml_node_names::elementUuidNode)
    {
        // name and uuid already extracted so nothing necessary to do
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
        boost::uuids::uuid evalUuid;
        boost::uuids::string_generator gen;

        try{
            evalName = it->second.get<std::string>(xml_node_names::elementNameNode);
            evalUuid = gen(it->second.get<std::string>(xml_node_names::elementUuidNode));
        } catch(boost::property_tree::ptree_error& pte) {
            throw InvalidXmlException(
                        std::string("Element not found: ") + pte.what());
        }

        boost::shared_ptr<Eval> newEval(new Eval(evalName, evalUuid));

        // now iterate through this whole node and construct all the elements
        for(boost::property_tree::ptree::const_iterator critIt = it->second.begin(); critIt != it->second.end(); ++critIt)
        {
            boost::property_tree::ptree criteriaPt = critIt->second;
            parseEvalItemNode(criteriaPt, critIt->first, newEval, gcIterFirst, gcIterLast);
        }

        student->addEval(newEval);
    }
}



#endif // STUDENTPROPERTYTREEPARSER_H
