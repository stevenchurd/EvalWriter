#ifndef GRADINGCRITERIAPROPERTYTREEPARSER_H
#define GRADINGCRITERIAPROPERTYTREEPARSER_H

#include <boost/property_tree/ptree.hpp>
#include <boost/foreach.hpp>
#include "xmlnodenames.h"

class GradingCriteriaPropertyTreeParser
{
public:
    GradingCriteriaPropertyTreeParser() {}
    virtual ~GradingCriteriaPropertyTreeParser() {}

    template <typename OutputIterator>
    void parseTree(boost::property_tree::ptree& pt, OutputIterator& dest);

private:

    template <typename OutputIterator>
    void parseGradingCriteriaNode(boost::property_tree::ptree& pt, OutputIterator& dest);


};


template <typename OutputIterator>
void GradingCriteriaPropertyTreeParser::parseTree(
        boost::property_tree::ptree& pt,
        OutputIterator& dest)
{
    BOOST_FOREACH(const boost::property_tree::ptree::value_type &v,
                  pt.get_child(gradingCriteriaRootNode))
    {
        // v.first is the name of the child.
        if(v.first != singleGradingCriteriaNode)
        {
            throw InvalidXmlException(
                    std::string("Expected gradingCriteria node: ") + v.first);
        }

        // v.second is the child tree.
        boost::property_tree::ptree gcPt = v.second;
        parseGradingCriteriaNode(gcPt, dest);
    }
}


template <typename OutputIterator>
void GradingCriteriaPropertyTreeParser::parseGradingCriteriaNode(
        boost::property_tree::ptree& pt, OutputIterator& dest)
{
    std::string gcName;

    try{
        gcName = pt.get<std::string>(elementNameNode);
    } catch(boost::property_tree::ptree_error& pte) {
        throw InvalidXmlException(
                    std::string("No name element found: ") + pte.what());
    }

    boost::shared_ptr<GradingCriteria> gc(new GradingCriteria(gcName));

    for (boost::property_tree::ptree::const_iterator it = pt.begin(); it != pt.end(); ++it)
    {
        std::string itemName;
        CriteriaItem::CriteriaItemLevelType itemLevel;

        if(it->first != singleCriteriaItemNode && it->first != elementNameNode)
        {
            throw InvalidXmlException(
                        std::string("Expected criteria item node: ") + it->first);
        }

        if(it->first == singleCriteriaItemNode)
        {
            try {
                itemName = it->second.get<std::string>(elementNameNode);
                itemLevel = static_cast<CriteriaItem::CriteriaItemLevelType>(
                            it->second.get<unsigned int>(criteriaItemLevelNode));
            } catch(boost::property_tree::ptree_error& pte) {
                throw InvalidXmlException(
                            std::string("Element not found: ") + pte.what());
            }

            gc->addCriteriaItem(itemName, itemLevel);
        }
    }

    dest++ = gc;
}


#endif // GRADINGCRITERIAPROPERTYTREEPARSER_H
