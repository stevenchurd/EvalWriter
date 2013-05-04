// (C) Copyright Steven Hurd 2013

#include "model/visitors/savevisitor.h"
#include <boost/property_tree/xml_parser.hpp>


SaveVisitor::SaveVisitor(boost::property_tree::ptree& pt) :
    Visitor(), m_pt(pt)
{
}


void SaveVisitor::saveFile(std::string& saveFile, boost::property_tree::ptree& pt)
{
    boost::property_tree::xml_parser::xml_writer_settings<char> w(' ', 4);
    boost::property_tree::xml_parser::write_xml(saveFile, pt, std::locale(), w);
}
