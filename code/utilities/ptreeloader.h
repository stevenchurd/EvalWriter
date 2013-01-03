#ifndef PTREELOADER_H
#define PTREELOADER_H

//TODO: remove
#if 0
#include <boost/property_tree/ptree.hpp>
#include "propertytreeparser.h"

class PtreeLoader
{
public:

    PtreeLoader(std::string filename, PropertyTreeParser& ptp) :
        m_filename(filename), m_ptParser(ptp) {}
    virtual ~PtreeLoader() {}

    void load(void);
    void processTree(void);

protected:
    boost::property_tree::ptree m_pt;

private:

    std::string m_filename;
    PropertyTreeParser& m_ptParser;

};


#endif
#endif // PTREELOADER_H
