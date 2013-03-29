#ifndef EVALSETPROPERTYTREEPARSER_H
#define EVALSETPROPERTYTREEPARSER_H

#include <boost/property_tree/ptree.hpp>

class EvalSetPropertyTreeParser
{
public:
    EvalSetPropertyTreeParser();
    virtual ~EvalSetPropertyTreeParser() {}

    template <typename OutputIterator>
    void parseTree(boost::property_tree::ptree& pt, OutputIterator& dest);
};


template <typename OutputIterator>
void EvalSetPropertyTreeParser::parseTree(boost::property_tree::ptree& pt, OutputIterator& dest)
{
#if 0
    // if the tree is empty, just return
    if(pt.empty())
        return;

    BOOST_FOREACH(boost::property_tree::ptree::value_type &v,
                  pt.get_child(coursesRootNode))
    {
        std::string courseName;
        boost::uuids::uuid courseUuid;
        boost::uuids::string_generator gen;

        // v.first is the name of the child.
        if(v.first != singleCourseNode)
        {
            throw InvalidXmlException(
                    std::string("Expected course node: ") + v.first);
        }

        try{
            courseName = v.second.get<std::string>(elementNameNode);
            courseUuid = gen(v.second.get<std::string>(elementUuidNode));
        } catch(boost::property_tree::ptree_error& pte) {
            throw InvalidXmlException(
                        std::string("Element not found: ") + pte.what());
        }

        boost::shared_ptr<Course> course(new Course(courseName, courseUuid));
        dest++ = course;
    }
#endif
}


#endif // EVALSETPROPERTYTREEPARSER_H
