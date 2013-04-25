// (C) Copyright Steven Hurd 2013

#ifndef COURSESPROPERTYTREEPARSER_H
#define COURSESPROPERTYTREEPARSER_H

#include <boost/property_tree/ptree.hpp>
#include "xmlnodenames.h"

class CoursesPropertyTreeParser
{
public:
    CoursesPropertyTreeParser() {}
    virtual ~CoursesPropertyTreeParser() {}

    template <typename OutputIterator>
    void parseTree(boost::property_tree::ptree& pt, OutputIterator& dest);

};


template <typename OutputIterator>
void CoursesPropertyTreeParser::parseTree(boost::property_tree::ptree& pt,
                                          OutputIterator& dest)
{
    // if the tree is empty, just return
    if(pt.empty() || pt.get_child_optional(xml_node_names::coursesRootNode) == nullptr)
        return;

    BOOST_FOREACH(boost::property_tree::ptree::value_type &v,
                  pt.get_child(xml_node_names::coursesRootNode))
    {
        std::string courseName;
        boost::uuids::uuid courseUuid;
        boost::uuids::string_generator gen;

        // v.first is the name of the child.
        if(v.first != xml_node_names::singleCourseNode)
        {
            throw InvalidXmlException(
                    std::string("Expected course node: ") + v.first);
        }

        try{
            courseName = v.second.get<std::string>(xml_node_names::elementNameNode);
            courseUuid = gen(v.second.get<std::string>(xml_node_names::elementUuidNode));
        } catch(boost::property_tree::ptree_error& pte) {
            throw InvalidXmlException(
                        std::string("Element not found: ") + pte.what());
        }

        boost::shared_ptr<Course> course(new Course(courseName, courseUuid));
        dest++ = course;
    }
}

#endif // COURSESPROPERTYTREEPARSER_H
