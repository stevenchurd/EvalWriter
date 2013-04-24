#ifndef TAGREPLACER_H
#define TAGREPLACER_H

#include <unordered_map>
#include <string>

#include "boost/shared_array.hpp"

class Eval;

class TagReplacer
{
public:
    TagReplacer();
    virtual ~TagReplacer() {}

    void addTag(std::string tagText, std::string replaceText);
    std::string performReplacement(std::string origString) const;

private:
    std::unordered_map<std::string, std::string> m_replacementTextMap;

};

boost::shared_ptr<TagReplacer> createTagReplacer(boost::shared_ptr<Eval> eval);

#ifdef _DEBUG
void testTagReplacer(void);
#endif

#endif // TAGREPLACER_H
