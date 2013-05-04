#ifndef EVALSETSAVEVISITOR_H
#define EVALSETSAVEVISITOR_H

#include "savevisitor.h"

class EvalSet;
class Eval;


class EvalSetSaveVisitor : public SaveVisitor
{
public:
    EvalSetSaveVisitor(boost::property_tree::ptree& parentPt);

    virtual ~EvalSetSaveVisitor() {}

    void visit(EvalSet& evalSet);
    void visit(Eval& eval);

private:
    std::list<boost::property_tree::ptree> m_subTrees;

};

#endif // EVALSETSAVEVISITOR_H
