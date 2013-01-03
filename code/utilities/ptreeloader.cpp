
#include "ptreeloader.h"
#include <boost/property_tree/xml_parser.hpp>

void PtreeLoader::load(void)
{
    boost::property_tree::xml_parser::read_xml(m_filename, m_pt);
}

void PtreeLoader::processTree(void)
{
    m_ptParser.parseTree(m_pt);
}
