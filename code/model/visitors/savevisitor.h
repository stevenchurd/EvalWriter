// (C) Copyright Steven Hurd 2013

#ifndef SAVEVISITOR_H
#define SAVEVISITOR_H

#include "visitor.h"
#include <boost/property_tree/ptree.hpp>

class SaveVisitor : public Visitor
{
public:
    SaveVisitor(boost::property_tree::ptree& pt);

    virtual ~SaveVisitor(void) {}

    static void saveFile(std::string &saveFile, boost::property_tree::ptree& pt) ;

protected:

    boost::property_tree::ptree& m_pt;

};



#endif // SAVEVISITOR_H
