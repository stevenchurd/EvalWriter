
#include "model/visitors/savevisitor.h"
#include <boost/property_tree/xml_parser.hpp>


void SaveVisitor::saveFile(std::string& saveFile)
{
    boost::property_tree::xml_parser::xml_writer_settings<char> w(' ', 4);
    boost::property_tree::xml_parser::write_xml(saveFile, m_pt, std::locale(), w);
}


void SaveVisitor::saveFile(std::ofstream& filestream)
{
    boost::property_tree::xml_parser::xml_writer_settings<char> w(' ', 4);
    boost::property_tree::xml_parser::write_xml(filestream, m_pt, w);
}
