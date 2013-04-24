#include "tagreplacer.h"
#include "evalexceptions.h"
#include "tagstrings.h"

#include <regex>
#include <sstream>
#include <QDebug>

TagReplacer::TagReplacer()
{
}


void TagReplacer::addTag(std::string tagText, std::string replaceText)
{
    // first make sure tag doesn't already exist
    auto it = m_replacementTextMap.find(tagText);

    // if the tag already existed, throw an exception
    if(it != m_replacementTextMap.end())
    {
        throw DuplicateItemException("Duplicate item: " + tagText);
    }

    m_replacementTextMap.insert(std::make_pair<std::string, std::string>(tagText, replaceText));
}


std::string TagReplacer::performReplacement(std::string origString) const
{
    std::string retString;
    std::string newString = origString;
    std::smatch sm;
    std::regex exp("<[^ >]*>");


    while(std::regex_search(newString, sm, exp))
    {
        qDebug() << QString::fromStdString(newString);
        qDebug() << QString::fromStdString(retString);

        auto tagSet = m_replacementTextMap.find(sm[0]);

        if(tagSet != m_replacementTextMap.end())
        {
            std::regex replaceExp(tagSet->first);
            newString = std::regex_replace(newString, replaceExp, tagSet->second);
        }
        else
        {
            if(sm.begin() != sm.end())
            {
                retString += sm.prefix() + sm[0];
                newString = sm.suffix();
            }
        }
    }
    retString += newString;

    qDebug() << QString::fromStdString(newString);
    qDebug() << QString::fromStdString(retString);

    return retString;
}
