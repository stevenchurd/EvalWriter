// (C) Copyright Steven Hurd 2013

#ifndef EVAL_H
#define EVAL_H

#include <boost/shared_ptr.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>

#include <vector>
#include <sstream>
#include <iostream>

#include "model/visitors/visitorelement.h"

class Visitor;
class EvalItem;

class Eval : public VisitorElement
{
public:
    enum Progress { New, InProgress, Complete };

    /*
     * Constructors/destructor
     */
    Eval(std::string evalName, Progress progress,
         boost::uuids::uuid objUuid = boost::uuids::random_generator()());

    virtual ~Eval() {}

    std::string getEvalName(void) const { return m_evalName; }
    void setEvalName(std::string name) { m_evalName = name; }

    void getPrintableEvalString(std::stringstream &ss) ;

    void addEvalItem(boost::shared_ptr<EvalItem> evalItem) ;
    void addEvalItemAt(int index, boost::shared_ptr<EvalItem> evalItem);
    void removeEvalItemAt(int index);
    void moveEvalItem(int oldPosition, int newPosition) ;
    void replaceEvalItem(boost::shared_ptr<EvalItem> newItem, std::string oldUuid);

    unsigned int getNumEvalItems(void) { return static_cast<unsigned int>(m_evalItems.size()); }

    boost::shared_ptr<EvalItem> getEvalItem(unsigned int index) const;

    void setProgressCompleted(void) { m_progress = Complete; }
    void setProgressInProgress(void) { m_progress = InProgress; }
    Progress getProgress(void) const { return m_progress; }

    std::string getUuid(void) const { return to_string(m_uuid); }

    /*
     * Visitor interface functions
     */
    void accept(Visitor& visitor);
    void acceptChildren(Visitor& visitor);

#ifdef _DEBUG
    void printItems(void);
#endif

private:
    std::string m_evalName;
    Progress m_progress;
    boost::uuids::uuid m_uuid;

    std::vector<boost::shared_ptr<EvalItem> > m_evalItems;

    // disable copy constructor and assignment
    Eval(const Eval&);
    Eval& operator= (const Eval&);


};

#endif // EVAL_H
