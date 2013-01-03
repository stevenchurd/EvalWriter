#ifndef SAVEVISITOR_H
#define SAVEVISITOR_H

#include "visitor.h"
#include <boost/property_tree/ptree.hpp>

class SaveVisitor : public Visitor
{
public:
    SaveVisitor() {}

    virtual ~SaveVisitor(void) {}

    void saveFile(std::string &saveFile) ;
    void saveFile(std::ofstream& filestream);

protected:

    boost::property_tree::ptree m_pt;

};



#endif // SAVEVISITOR_H
