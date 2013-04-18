#ifndef CONTAINERINSERTVISITOR_H
#define CONTAINERINSERTVISITOR_H

#include "visitor.h"
#include "boost/any.hpp"

template <typename T>
class ContainerInsertVisitor : public Visitor
{
public:
    ContainerInsertVisitor(T& dest):
        Visitor(),
        m_dest(dest)
    {
    }

    ~ContainerInsertVisitor() {}

    void visit(EvalSet &);
    void visit(Eval& ) {}

    void visit(GradingCriteria& );



private:
    T& m_dest;
};


template <typename T>
void ContainerInsertVisitor<T>::visit(EvalSet& evalSet)
{
    std::for_each(evalSet.evalSetsBegin(), evalSet.evalSetsEnd(),
                  [this] (boost::shared_ptr<EvalSet> subEvalSet)
    {
        m_dest.insert(std::make_pair<std::string, boost::any>(
                          subEvalSet->getUuid(), subEvalSet));
    });

    evalSet.acceptChildren(*this);
}


template <typename T>
void ContainerInsertVisitor<T>::visit(GradingCriteria& gc)
{
    for(unsigned int i = 0; i < gc.getNumCriteriaItems(); i++)
    {
        boost::shared_ptr<CriteriaItem> ci;
        ci = gc.getCriteriaItemAt(i);
        m_dest.insert(std::make_pair<std::string, boost::any>(
                          ci->getUuid(), ci));
    }
}

#endif // CONTAINERINSERTVISITOR_H
