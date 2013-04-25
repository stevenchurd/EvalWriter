// (C) Copyright Steven Hurd 2013

#include "evalset.h"
#include "eval.h"
#include "visitors/visitor.h"

EvalSet::EvalSet(std::string name,
                 boost::shared_ptr<EvalSet> parentEvalSet,
                 boost::uuids::uuid objUuid) :
    VisitorElement(),
    m_evalSetName(name),
    m_parentEvalSet(parentEvalSet),
    m_uuid(objUuid)
{
}


unsigned int EvalSet::addEval(boost::shared_ptr<Eval> newEval)
{
    auto it = std::find_if(m_evals.begin(), m_evals.end(),
                           [&newEval] (boost::shared_ptr<Eval> eval)
                           { return (newEval < eval); });

    unsigned int row = std::distance(m_evals.begin(), it);
    m_evals.insert(it, newEval);
    return row;
}


std::vector<boost::shared_ptr<Eval> >::const_iterator EvalSet::evalsBegin(void)
{
    return m_evals.cbegin();
}


std::vector<boost::shared_ptr<Eval> >::const_iterator EvalSet::evalsEnd(void)
{
    return m_evals.cend();
}


void EvalSet::removeEval(std::vector<boost::shared_ptr<Eval> >::const_iterator it)
{
    m_evals.erase(it);
}


void EvalSet::removeEval(std::vector<std::string> uuids)
{
    m_evals.erase(std::remove_if(m_evals.begin(), m_evals.end(),
                   [&uuids] (boost::shared_ptr<Eval> eval)
                   { return (std::find(uuids.begin(), uuids.end(), eval->getUuid()) != uuids.end()); }),
            m_evals.end());
}


std::vector<boost::shared_ptr<EvalSet> >::const_iterator EvalSet::evalSetsBegin(void)
{
    return m_subEvalSets.cbegin();
}


std::vector<boost::shared_ptr<EvalSet> >::const_iterator EvalSet::evalSetsEnd(void)
{
    return m_subEvalSets.cend();
}


bool EvalSet::containsEval(std::string uuid) const
{
    auto it = std::find_if(m_evals.begin(), m_evals.end(),
                           [&uuid] (boost::shared_ptr<Eval> eval)
                           { return (eval->getUuid() == uuid); });

    return (it != m_evals.end());
}


unsigned int EvalSet::addEvalSet(boost::shared_ptr<EvalSet> newEvalSet)
{
    auto it = std::find_if(m_subEvalSets.begin(), m_subEvalSets.end(),
                           [&newEvalSet] (boost::shared_ptr<EvalSet> evalSet)
                           { return (newEvalSet < evalSet); });

    unsigned int row = std::distance(m_subEvalSets.begin(), it);
    m_subEvalSets.insert(it, newEvalSet);
    return row;
}


void EvalSet::removeEvalSet(std::vector<boost::shared_ptr<EvalSet> >::const_iterator it)
{
    m_subEvalSets.erase(it);
}


void EvalSet::accept(Visitor& visitor)
{
    visitor.visit(*this);
}


void EvalSet::acceptChildren(Visitor& visitor)
{
    std::for_each(m_subEvalSets.begin(), m_subEvalSets.end(),
                  [&visitor] (boost::shared_ptr<EvalSet> evalSet)
    {
        evalSet->accept(visitor);
    });

    std::for_each(m_evals.begin(), m_evals.end(),
                  [&visitor] (boost::shared_ptr<Eval> eval)
    {
        eval->accept(visitor);
    });
}


bool EvalSet::operator== (const EvalSet& rhs) const
{
    return (getUuid() == rhs.getUuid());
}


bool operator<(const boost::shared_ptr<EvalSet>& lhs, const boost::shared_ptr<EvalSet>& rhs)
{
    return (lhs->getEvalSetName() < rhs->getEvalSetName());
}

