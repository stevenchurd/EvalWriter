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

    std::string getEvalSetName(void) const { return m_evalSetName; }
    void updateEvalSetName(std::string newName) { m_evalSetName = newName; }

    void addEval(boost::shared_ptr<Eval> eval);
    void removeEval(std::vector<boost::shared_ptr<Eval> >::const_iterator it);

    std::vector<boost::shared_ptr<Eval> >::const_iterator evalsBegin(void);
    std::vector<boost::shared_ptr<Eval> >::const_iterator evalsEnd(void);

    void addEvalSet(boost::shared_ptr<EvalSet> evalSet);
    void removeEvalSet(std::vector<boost::shared_ptr<EvalSet> >::const_iterator it);

    std::vector<boost::shared_ptr<EvalSet> >::const_iterator evalSetsBegin(void);
    std::vector<boost::shared_ptr<EvalSet> >::const_iterator evalSetsEnd(void);

    /*
     * VisitorElement functions
     */
    void accept(Visitor& visitor) { visitor.visit(*this); }
    void acceptChildren(Visitor& visitor);

private:
    std::string m_evalSetName;
    std::vector<boost::shared_ptr<Eval> > m_evals;
    std::vector<boost::shared_ptr<EvalSet> > m_subEvalSets;

    // disable copy constructor and assignment
    EvalSet(const EvalSet&);
    EvalSet& operator= (const EvalSet&);

};

#endif // EVALSET_H
