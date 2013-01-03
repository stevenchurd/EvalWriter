#ifndef VISITORELEMENT_H
#define VISITORELEMENT_H

#include <stdexcept>

class Visitor;

class VisitorElement
{
public:
    VisitorElement() {}
    virtual void accept(Visitor& object) = 0;

    virtual void acceptChildren(Visitor& )
    {
        throw std::runtime_error("Accept children not implemented for this class");
    }
};

#endif // VISITORELEMENT_H
