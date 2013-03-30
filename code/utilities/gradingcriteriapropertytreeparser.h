// (C) Copyright Steven Hurd 2013

#ifndef GRADINGCRITERIAPROPERTYTREEPARSER_H
#define GRADINGCRITERIAPROPERTYTREEPARSER_H

#include <boost/property_tree/ptree.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/string_generator.hpp>
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
    // if the tree is empty, just return
    if(pt.empty() || pt.get_child_optional(xml_node_names::gradingCriteriaRootNode) == nullptr)
        return;

    BOOST_FOREACH(const boost::property_tree::ptree::value_type &v,
                  pt.get_child(xml_node_names::gradingCriteriaRootNode))
    {
        // v.first is the name of the child.
        if(v.first != xml_node_names::singleGradingCriteriaNode)
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
    boost::uuids::uuid gcUuid;
    boost::uuids::string_generator gen;

    try{
        gcName = pt.get<std::string>(xml_node_names::elementNameNode);
        gcUuid = gen(pt.get<std::string>(xml_node_names::elementUuidNode));
    } catch(boost::property_tree::ptree_error& pte) {
        throw InvalidXmlException(
                    std::string("Element not found: ") + pte.what());
    }

    boost::shared_ptr<GradingCriteria> gc(new GradingCriteria(gcName, gcUuid));

    for (boost::property_tree::ptree::const_iterator it = pt.begin(); it != pt.end(); ++it)
    {
        std::string itemName;
        CriteriaItem::CriteriaItemLevelType itemLevel;
        boost::uuids::uuid itemUuid;
        boost::uuids::string_generator gen;

        // check the keys to make sure this is XML that we are expecting
        if(it->first != xml_node_names::singleCriteriaItemNode &&
                it->first != xml_node_names::elementNameNode &&
                it->first != xml_node_names::elementUuidNode)
        {
            throw InvalidXmlException(
                        std::string("Unexpected key under gradingCriteria node: ") + it->first);
        }

        if(it->first == xml_node_names::singleCriteriaItemNode)
        {
            try {
                itemName = it->second.get<std::string>(xml_node_names::elementNameNode);
                itemLevel = static_cast<CriteriaItem::CriteriaItemLevelType>(
                            it->second.get<unsigned int>(xml_node_names::criteriaItemLevelNode));
                itemUuid = gen(it->second.get<std::string>(xml_node_names::elementUuidNode));
            } catch(boost::property_tree::ptree_error& pte) {
                throw InvalidXmlException(
                            std::string("Element not found: ") + pte.what());
            }

            gc->addExistingCriteriaItem(itemName, itemLevel, itemUuid);
        }
    }

    dest++ = gc;
}


#endif // GRADINGCRITERIAPROPERTYTREEPARSER_H
