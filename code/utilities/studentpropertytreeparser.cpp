// (C) Copyright Steven Hurd 2013

#include <sstream>

#include "studentpropertytreeparser.h"
#include "xmlnodenames.h"
#include "evalexceptions.h"

#include "model/student.h"
#include "model/course.h"
#include "model/eval.h"
#include "model/criteriaitem.h"
#include "model/gradingcriteria.h"
#include "model/customtextitem.h"

void StudentPropertyTreeParser::parseCustomTextNode(
        boost::property_tree::ptree& pt,
        boost::shared_ptr<Eval>& eval)
{
    std::string customText;
    std::string customTextTitle;
    boost::uuids::uuid ctUuid;
    boost::uuids::string_generator gen;

    try {
        customText = pt.get<std::string>(xml_node_names::elementValueNode);
        customTextTitle = pt.get<std::string>(xml_node_names::elementTitleNode);
        ctUuid = gen(pt.get<std::string>(xml_node_names::elementUuidNode));
    } catch(boost::property_tree::ptree_error& pte) {
        throw InvalidXmlException(
                    std::string("Node not found: ") + pte.what());
    }

    boost::shared_ptr<CustomTextItem> cti(new CustomTextItem(customTextTitle, customText, ctUuid));
    eval->addEvalItem(cti);
}

