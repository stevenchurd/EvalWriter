#ifndef EVALSETPROPERTYTREEPARSER_H
#define EVALSETPROPERTYTREEPARSER_H

#include <boost/property_tree/ptree.hpp>
#include "xmlnodenames.h"
#include "model/evalset.h"

class EvalSetPropertyTreeParser
{
public:
    EvalSetPropertyTreeParser();
    virtual ~EvalSetPropertyTreeParser() {}

    template <typename OutputIterator, typename InputIterator>
    void parseTree(boost::property_tree::ptree& pt, OutputIterator& dest,
                   InputIterator& studentsBegin, InputIterator& studentsEnd);

private:
    template <typename InputIterator>
    boost::shared_ptr<EvalSet> parseEvalSetNode(boost::property_tree::ptree& pt,
                                                InputIterator& studentsBegin,
                                                InputIterator& studentsEnd);

    template <typename InputIterator>
    boost::shared_ptr<Eval> parseEvalNode(boost::property_tree::ptree& pt,
                                          InputIterator& studentsBegin,
                                          InputIterator& studentsEnd);

};


template <typename OutputIterator, typename InputIterator>
void EvalSetPropertyTreeParser::parseTree(boost::property_tree::ptree& pt,
                                          OutputIterator& dest,
                                          InputIterator& studentsBegin,
                                          InputIterator& studentsEnd)
{
    // if the tree is empty, just return
    if(pt.empty() || pt.get_child_optional(xml_node_names::evalSetsRootNode) == nullptr)
        return;

    BOOST_FOREACH(boost::property_tree::ptree::value_type &v,
                  pt.get_child(xml_node_names::evalSetsRootNode))
    {
        if(v.first != xml_node_names::singleEvalSetNode)
        {
            throw InvalidXmlException(
                    std::string("Expected evalSet node: ") + v.first);
        }

        dest++ = parseEvalSetNode(v.second, studentsBegin, studentsEnd);
    }
}

template <typename InputIterator>
boost::shared_ptr<EvalSet> EvalSetPropertyTreeParser::parseEvalSetNode(boost::property_tree::ptree& pt,
                                            InputIterator& studentsBegin, InputIterator& studentsEnd)
{
    std::string evalSetTitle;
    boost::uuids::uuid evalSetUuid;
    boost::uuids::string_generator gen;

    try{
        evalSetTitle = pt.get<std::string>(xml_node_names::elementTitleNode);
        evalSetUuid = gen(pt.get<std::string>(xml_node_names::elementUuidNode));
    } catch(boost::property_tree::ptree_error& pte) {
        throw InvalidXmlException(
                    std::string("Element not found: ") + pte.what());
    }

    boost::shared_ptr<EvalSet> evalSet(new EvalSet(evalSetTitle, evalSetUuid));

    for (auto it = pt.begin(); it != pt.end(); ++it)
    {
        if(it->first == xml_node_names::singleEvalSetNode)
        {
            evalSet->addEvalSet(parseEvalSetNode(it->second, studentsBegin, studentsEnd));
        }
        else if(it->first == xml_node_names::singleEvalNode)
        {
            evalSet->addEval(parseEvalNode(it->second, studentsBegin, studentsEnd));
        }
        else if(it->first == xml_node_names::elementTitleNode ||
                it->first == xml_node_names::elementUuidNode)
        {
            // title and UUID have already been extracted, ignore them
        }
        else
        {
            throw InvalidXmlException("Invalid node found in EvalSet tree: " + it->first);
        }
    }

    return evalSet;
}



template <typename InputIterator>
boost::shared_ptr<Eval> EvalSetPropertyTreeParser::parseEvalNode(boost::property_tree::ptree& pt,
                                            InputIterator& studentsBegin, InputIterator& studentsEnd)
{
    boost::uuids::uuid evalUuid;
    boost::uuids::string_generator gen;

    try{
        evalUuid = gen(pt.get<std::string>(xml_node_names::elementUuidNode));
    } catch(boost::property_tree::ptree_error& pte) {
        throw InvalidXmlException(
                    std::string("Element not found: ") + pte.what());
    }

    boost::shared_ptr<Eval> eval;

    std::find_if(studentsBegin, studentsEnd,
                 [&evalUuid, &eval] (boost::shared_ptr<Student> student)
                 { return student->getEvalById(to_string(evalUuid), eval); });

    if(eval == nullptr)
    {
        throw InvalidXmlException("Eval not found: " + to_string(evalUuid));
    }

    return eval;
}

#endif // EVALSETPROPERTYTREEPARSER_H
