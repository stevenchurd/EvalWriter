// (C) Copyright Steven Hurd 2013

#ifndef EVAL_H
#define EVAL_H

#include <boost/shared_ptr.hpp>
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
    Eval(std::string evalName);
    virtual ~Eval() {}

    std::string getEvalName(void) const { return m_evalName; }

    void getPrintableEvalString(std::stringstream &ss) ;

    void addEvalItem(boost::shared_ptr<EvalItem> evalItem) ;
    void removeEvalItem(EvalItem::ItemUniqueIdType itemId) ;
    void moveEvalItem(int oldPosition, int newPosition) ;
    void replaceEvalItem(boost::shared_ptr<EvalItem> newItem, int oldId);

    int getNumEvalItems(void) { return m_evalItems.size(); }

    boost::shared_ptr<EvalItem> getEvalItem(unsigned int index) const;

    /*
     * Visitor interface functions
     */
    void accept(Visitor& visitor) { visitor.visit(*this); }
    void acceptChildren(Visitor& visitor);

private:
    std::string m_evalName;

    std::vector<boost::shared_ptr<EvalItem> > m_evalItems;

    // disable copy constructor and assignment
    Eval(const Eval&);
    Eval& operator= (const Eval&);


};

#endif // EVAL_H
