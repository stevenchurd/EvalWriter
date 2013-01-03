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
    BOOST_FOREACH(boost::property_tree::ptree::value_type &v,
                  pt.get_child(coursesRootNode))
    {
        boost::shared_ptr<Course> course(new Course(v.second.data()));
        dest++ = course;
    }
}

#endif // COURSESPROPERTYTREEPARSER_H
