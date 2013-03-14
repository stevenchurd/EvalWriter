// (C) Copyright Steven Hurd 2013

#ifndef EVALSET_H
#define EVALSET_H

#include "visitors/visitorelement.h"
#include "eval.h"
#include "boost/shared_ptr.hpp"

class EvalSet : public VisitorElement
{
public:
    EvalSet(std::string name);

    virtual ~EvalSet() {}

    void addEval(boost::shared_ptr<Eval> eval);
    boost::shared_ptr<Eval> getEval(unsigned int) const;
    void removeEval(unsigned int);

    void addEvalSet(boost::shared_ptr<EvalSet> evalSet);
    boost::shared_ptr<EvalSet> getEvalSet(unsigned int) const;
    void removeEvalSet(unsigned int);

    /*
     * VisitorElement functions
     */
    void accept(Visitor& visitor) { visitor.visit(*this); }
    void acceptChildren(Visitor& visitor);

private:
    std::string m_evalSetName;
    std::vector<boost::shared_ptr<Eval> > m_evalSet;
    std::vector<boost::shared_ptr<EvalSet> > m_subEvalSets;

    // disable copy constructor and assignment
    EvalSet(const EvalSet&);
    EvalSet& operator= (const EvalSet&);

};

#endif // EVALSET_H
