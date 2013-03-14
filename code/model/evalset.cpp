// (C) Copyright Steven Hurd 2013

#include "evalset.h"

EvalSet::EvalSet(std::string name) : VisitorElement(),
    m_evalSetName(name)
{
}


void EvalSet::addEval(boost::shared_ptr<Eval> eval)
{
    m_evalSet.push_back(eval);
}


boost::shared_ptr<Eval> EvalSet::getEval(unsigned int index) const
{
    if(index > m_evalSet.size())
        throw ItemNotFoundException("Invalid item for removal: " + index);

    return m_evalSet[index];
}


void EvalSet::removeEval(unsigned int index)
{
    if(index > m_evalSet.size())
        throw ItemNotFoundException("Invalid item for removal: " + index);

    m_evalSet.erase(std::next(m_evalSet.begin(), index));
}


void EvalSet::addEvalSet(boost::shared_ptr<EvalSet> evalSet)
{
    m_subEvalSets.push_back(evalSet);
}


boost::shared_ptr<EvalSet> EvalSet::getEvalSet(unsigned int index) const
{
    if(index > m_subEvalSets.size())
        throw ItemNotFoundException("Invalid item for removal: " + index);

    return m_subEvalSets[index];
}


void EvalSet::removeEvalSet(unsigned int index)
{
    if(index > m_subEvalSets.size())
        throw ItemNotFoundException("Invalid item for removal: " + index);

    m_subEvalSets.erase(std::next(m_subEvalSets.begin(), index));
}


void EvalSet::acceptChildren(Visitor& visitor)
{
    std::for_each(m_evalSet.begin(), m_evalSet.end(),
                  [&visitor] (boost::shared_ptr<Eval> eval) {
                      eval->accept(visitor);
                  });
}
