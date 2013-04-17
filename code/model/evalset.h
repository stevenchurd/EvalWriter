// (C) Copyright Steven Hurd 2013

#ifndef EVALSET_H
#define EVALSET_H

#include <vector>

#include "visitors/visitorelement.h"

#include "boost/shared_ptr.hpp"
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>

class Visitor;
class Eval;

class EvalSet : public VisitorElement
{
public:
    EvalSet(std::string name,
            boost::shared_ptr<EvalSet> parentEvalSet,
            boost::uuids::uuid objUuid = boost::uuids::random_generator()());

    virtual ~EvalSet() {}

    std::string getEvalSetName(void) const { return m_evalSetName; }
    void updateEvalSetName(std::string newName) { m_evalSetName = newName; }

    void addEval(boost::shared_ptr<Eval> eval);
    void removeEval(std::vector<boost::shared_ptr<Eval> >::const_iterator it);
    void removeEval(std::vector<std::string> uuids);

    std::vector<boost::shared_ptr<Eval> >::const_iterator evalsBegin(void);
    std::vector<boost::shared_ptr<Eval> >::const_iterator evalsEnd(void);

    void addEvalSet(boost::shared_ptr<EvalSet> evalSet);
    void removeEvalSet(std::vector<boost::shared_ptr<EvalSet> >::const_iterator it);

    std::vector<boost::shared_ptr<EvalSet> >::const_iterator evalSetsBegin(void);
    std::vector<boost::shared_ptr<EvalSet> >::const_iterator evalSetsEnd(void);

    std::string getUuid(void) const { return to_string(m_uuid); }
    boost::shared_ptr<EvalSet> getParentEvalSet(void) const { return m_parentEvalSet; }

    bool containsEval(std::string uuid) const;

    /*
     * VisitorElement functions
     */
    void accept(Visitor& visitor);
    void acceptChildren(Visitor& visitor);

private:
    std::string m_evalSetName;
    std::vector<boost::shared_ptr<Eval> > m_evals;
    std::vector<boost::shared_ptr<EvalSet> > m_subEvalSets;
    boost::shared_ptr<EvalSet> m_parentEvalSet;

    boost::uuids::uuid m_uuid;

    // disable copy constructor and assignment
    EvalSet(const EvalSet&);
    EvalSet& operator= (const EvalSet&);

};

#endif // EVALSET_H
