// (C) Copyright Steven Hurd 2013

#ifndef EVAL_H
#define EVAL_H

#include <boost/shared_ptr.hpp>
#include <list>
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
    Eval(std::string evalName);
    virtual ~Eval() {}

    std::string getEvalName(void) const { return m_evalName; }

    void getPrintableEvalString(std::stringstream &ss) ;

    void addEvalItem(boost::shared_ptr<EvalItem> evalItem) ;
    void removeEvalItem(EvalItem::ItemUniqueIdType itemId) ;
    void moveEvalItem(int oldPosition, int newPos) ;
    void replaceEvalItem(boost::shared_ptr<EvalItem> newItem, int oldId);

    size_t getNumEvalItems(void) { return m_evalItems.size(); }

    /*
     * Visitor interface functions
     */
    void accept(Visitor& visitor) { visitor.visit(*this); }
    void acceptChildren(Visitor& visitor);

private:
    std::string m_evalName;

    std::list<boost::shared_ptr<EvalItem> > m_evalItems;

    // disable copy constructor and assignment
    Eval(const Eval&);
    Eval& operator= (const Eval&);


};

#endif // EVAL_H
