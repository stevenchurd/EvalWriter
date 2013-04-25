// (C) Copyright Steven Hurd 2013

#ifndef EVALEXCEPTIONS_H
#define EVALEXCEPTIONS_H

#include <stdexcept>
#include <string>

class InvalidVisitorException : public std::runtime_error
{
public:
    InvalidVisitorException(std::string const& msg) : runtime_error(msg) {}
    virtual ~InvalidVisitorException() {}
};


class InvalidXmlException : public std::runtime_error
{
public:
    InvalidXmlException(std::string const& msg) : runtime_error(msg) {}
    virtual ~InvalidXmlException() {}
};


class ItemNotFoundException : public std::runtime_error
{
public:
    ItemNotFoundException(std::string const& msg) : runtime_error(msg) {}
    virtual ~ItemNotFoundException() {}
};

class DuplicateItemException : public std::runtime_error
{
public:
    DuplicateItemException(std::string const& msg) : runtime_error(msg) {}
    virtual ~DuplicateItemException() {}
};


class UnexpectedModelException : public std::runtime_error
{
public:
    UnexpectedModelException(std::string const& msg) : runtime_error(msg) {}
    virtual ~UnexpectedModelException() {}
};


class GenericModelException : public std::runtime_error
{
public:
    GenericModelException(std::string const& msg) : runtime_error(msg) {}
    virtual ~GenericModelException() {}
};

#endif // EVALEXCEPTIONS_H
