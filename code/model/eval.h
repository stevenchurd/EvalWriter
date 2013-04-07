// (C) Copyright Steven Hurd 2013

#ifndef EVAL_H
#define EVAL_H

#include <boost/shared_ptr.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>

#include <vector>
#include <sstream>
#include <iostream>

#include "evalitem.h"
#include "model/visitors/visitor.h"
#include "model/visitors/visitorelement.h"

class Eval : public VisitorElement
{
public:

    /*
     * Constructors/destructor
     */
    Eval(std::string evalName,
         boost::uuids::uuid objUuid = boost::uuids::random_generator()());

    virtual ~Eval() {}

    std::string getEvalName(void) const { return m_evalName; }
    void setEvalName(std::string name) { m_evalName = name; }

    void getPrintableEvalString(std::stringstream &ss) ;

    void addEvalItem(boost::shared_ptr<EvalItem> evalItem) ;
    void addEvalItemAt(int index, boost::shared_ptr<EvalItem> evalItem);
    void removeEvalItemAt(int index);
    void moveEvalItem(int oldPosition, int newPosition) ;
    void replaceEvalItem(boost::shared_ptr<EvalItem> newItem, std::string oldUuid);

    int getNumEvalItems(void) { return m_evalItems.size(); }

    boost::shared_ptr<EvalItem> getEvalItem(unsigned int index) const;

    std::string getUuid(void) const { return to_string(m_uuid); }

    /*
     * Visitor interface functions
     */
    void accept(Visitor& visitor) { visitor.visit(*this); }
    void acceptChildren(Visitor& visitor);

#ifdef _DEBUG
    void printItems(void);
#endif

private:
    std::string m_evalName;
    boost::uuids::uuid m_uuid;

    std::vector<boost::shared_ptr<EvalItem> > m_evalItems;

    // disable copy constructor and assignment
    Eval(const Eval&);
    Eval& operator= (const Eval&);


};

#endif // EVAL_H
