// (C) Copyright Steven Hurd 2013

#include "eval.h"
#include "evalitem.h"
#include "customtextitem.h"
#include "visitors/visitor.h"
#include <boost/algorithm/string.hpp>

#ifdef _DEBUG
#include <QDebug>
#endif

Eval::Eval(std::string evalName, Progress progress,
           boost::uuids::uuid objUuid) :
    VisitorElement(), m_evalName(evalName),
    m_progress(progress), m_uuid(objUuid)
{
}


Eval::Eval(std::string evalName, const Eval& eval) :
    VisitorElement(), m_evalName(evalName),
    m_progress(New), m_uuid(boost::uuids::random_generator()())
{
    for(unsigned int i = 0; i < eval.getNumEvalItems(); i++)
    {
        boost::shared_ptr<EvalItem> oldEvalItem = eval.getEvalItem(i);

        // copying a custom text item requires us to create a new one
        // so that it can get a unique uuid
        if(typeid(*oldEvalItem) == typeid(CustomTextItem))
        {
            boost::shared_ptr<EvalItem> newCustomText(new CustomTextItem(oldEvalItem->getItemTitleStr(),
                                                                         oldEvalItem->getItemStr()));
            oldEvalItem = newCustomText;
        }

        m_evalItems.push_back(oldEvalItem);
    }
}


void Eval::getPrintableEvalString(std::stringstream& ss)
{
    for(auto it = m_evalItems.begin();
        it != m_evalItems.end(); it++)
    {
        ss << boost::algorithm::trim_copy((*it)->getItemStr()) << "  ";
    }
}


void Eval::addEvalItem(boost::shared_ptr<EvalItem> evalItem)
{
    m_evalItems.push_back(evalItem);
}


void Eval::addEvalItemAt(int index, boost::shared_ptr<EvalItem> evalItem)
{
    m_evalItems.insert(std::next(m_evalItems.begin(), index), evalItem);
}


void Eval::removeEvalItemAt(int index)
{
    m_evalItems.erase(std::next(m_evalItems.begin(), index));
}


void Eval::moveEvalItem(int oldPosition, int newPosition)
{
    if(oldPosition+1 == newPosition || oldPosition-1 == newPosition)
    {
        std::iter_swap(std::next(m_evalItems.begin(), oldPosition),
                       std::next(m_evalItems.begin(), newPosition));
    }
    else if(oldPosition < newPosition)
    {
        // if the old position is to the left of the new position, rotate left
        std::rotate(std::next(m_evalItems.begin(), oldPosition),
                    std::next(m_evalItems.begin(), oldPosition+1),
                    std::next(m_evalItems.begin(), newPosition+1));
    }
    else if(oldPosition > newPosition)
    {
        // if it's to the right rotate right
        std::rotate(std::next(m_evalItems.rbegin(), m_evalItems.size()-oldPosition-1),
                    std::next(m_evalItems.rbegin(), m_evalItems.size()-oldPosition),
                    std::next(m_evalItems.rbegin(), m_evalItems.size()-newPosition));
    }
}


void Eval::replaceEvalItem(boost::shared_ptr<EvalItem> newItem, std::string oldUuid)
{
    std::replace_if(m_evalItems.begin(), m_evalItems.end(),
                    [&oldUuid] (boost::shared_ptr<EvalItem> ei) { return (oldUuid == ei->getUuid()); },
                    newItem);
}


boost::shared_ptr<EvalItem> Eval::getEvalItem(unsigned int index) const
{
    if(index > m_evalItems.size())
    {
        throw ItemNotFoundException("Item not found: " + index);
    }

    return m_evalItems[index];
}


void Eval::accept(Visitor& visitor)
{
    visitor.visit(*this);
}


void Eval::acceptChildren(Visitor& visitor)
{
    std::for_each(m_evalItems.begin(), m_evalItems.end(),
                  [&visitor](boost::shared_ptr<EvalItem> evalItem){
                      evalItem->accept(visitor);
                  });
}


bool Eval::operator==(const Eval& rhs) const
{
    return (getUuid() == rhs.getUuid());
}


bool operator<(const boost::shared_ptr<Eval>& rhs, const boost::shared_ptr<Eval>& lhs)
{
    return (rhs->getEvalName() < lhs->getEvalName());
}


#ifdef _DEBUG
    void Eval::printItems(void)
    {
        qDebug("____________________________");

        std::for_each(m_evalItems.begin(), m_evalItems.end(),
                    [](boost::shared_ptr<EvalItem> evalItem) {
                        qDebug() << "UniqueId: " << QString::fromStdString(evalItem->getUuid()) <<
                                    " Item: " << QString::fromStdString(evalItem->getItemStr());
                    });

       qDebug("____________________________");
    }
#endif
