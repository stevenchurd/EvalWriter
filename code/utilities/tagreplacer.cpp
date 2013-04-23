#include "tagreplacer.h"
#include "evalexceptions.h"

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
    std::string newString = origString;
    std::smatch m;
    std::regex e("<.*>");

    while (std::regex_search (origString,m,e)) {
        for(auto it = m.begin(); it != m.end(); ++it)
        {
            qDebug() << QString::fromStdString(*it);
        }
    }

    return std::string();
}
