// (C) Copyright Steven Hurd 2013

#include "evalset.h"

EvalSet::EvalSet(std::string name,
                 boost::uuids::uuid objUuid) :
    VisitorElement(),
    m_evalSetName(name),
    m_uuid(objUuid)
{
}


void EvalSet::addEval(boost::shared_ptr<Eval> eval)
{
    m_evals.push_back(eval);
}


std::vector<boost::shared_ptr<Eval> >::const_iterator EvalSet::evalsBegin(void)
{
    return m_evals.begin();
}


std::vector<boost::shared_ptr<Eval> >::const_iterator EvalSet::evalsEnd(void)
{
    return m_evals.end();
}


std::vector<boost::shared_ptr<EvalSet> >::const_iterator EvalSet::evalSetsBegin(void)
{
    return m_subEvalSets.begin();
}


std::vector<boost::shared_ptr<EvalSet> >::const_iterator EvalSet::evalSetsEnd(void)
{
    return m_subEvalSets.end();
}


void EvalSet::addEvalSet(boost::shared_ptr<EvalSet> evalSet)
{
    m_subEvalSets.push_back(evalSet);
}


void EvalSet::removeEvalSet(std::vector<boost::shared_ptr<EvalSet> >::const_iterator it)
{
    m_subEvalSets.erase(it);
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
