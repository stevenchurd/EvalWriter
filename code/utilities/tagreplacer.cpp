#include "tagreplacer.h"
#include "evalexceptions.h"
#include "persistentdatamanager.h"

#include "model/eval.h"
#include "model/student.h"

#include <regex>

#ifdef _DEBUG
#include "tagstrings.h"
#include <QDebug>
#endif

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
        auto tagSet = m_replacementTextMap.find(sm[0]);

        if(tagSet != m_replacementTextMap.end())
        {
            std::regex replaceExpWithCap("(?<=[.:?!]\\s)" + tagSet->first);
            std::regex replaceExpNoCap(tagSet->first);

            newString = std::regex_replace(newString, replaceExpWithCap, tagSet->second);
            newString = std::regex_replace(newString, replaceExpNoCap, tagSet->second);
        }
        else
        {
            // if the tag doesn't exist in the map, just skip it
            if(sm.begin() != sm.end())
            {
                retString.append(sm.prefix());
                retString.append(sm[0]);
                newString = sm.suffix();
            }
        }
    }

    retString.append(newString);

    return retString;
}


//
// non-member, non-friend helper functions
//

// create a tag replacer based on an eval
boost::shared_ptr<TagReplacer> createTagReplacer(boost::shared_ptr<Eval> eval)
{
    // first find the student that this eval belongs to.
    auto it = std::find_if(PDM().studentsBegin(), PDM().studentsEnd(),
                 [&eval] (boost::shared_ptr<Student> student)->bool
                 {
                     boost::shared_ptr<Eval> myEval;
                     return (student->getEvalById(eval->getUuid(), myEval));
                 });

    // create all the tags that we will be replacing
    boost::shared_ptr<Student> student = *it;
    boost::shared_ptr<TagReplacer> newReplacer(new TagReplacer());

    newReplacer->addTag(TagStrings::studentFirstLastName, student->getFirstName() + " " + student->getLastName());
    newReplacer->addTag(TagStrings::studentFirstName, student->getFirstName());
    newReplacer->addTag(TagStrings::studentLastName, student->getLastName());
    newReplacer->addTag(TagStrings::studentMiddleName, student->getMiddleName());

    // gender based strings (0 = female, 1 = male)
    newReplacer->addTag(TagStrings::studentHeShe, (student->getGender()) ? "he" : "she");
    newReplacer->addTag(TagStrings::studentHimHer, (student->getGender()) ? "him" : "her");
    newReplacer->addTag(TagStrings::studentHimselfHerself, (student->getGender()) ? "himself" : "herself");
    newReplacer->addTag(TagStrings::studentHisHer, (student->getGender()) ? "his" : "her");

    return newReplacer;
}


#ifdef _DEBUG
void testTagReplacer(void)
{
    std::string testString = TagStrings::studentFirstLastName + " " + TagStrings::studentMiddleName + " " +
            TagStrings::studentLastName + " " + TagStrings::studentHimselfHerself + " " +
            TagStrings::studentFirstName + TagStrings::studentFirstLastName;
    qDebug() << QString::fromStdString(testString);
    TagReplacer tagReplacer;
    tagReplacer.addTag(TagStrings::studentFirstLastName, "John Earp");
    tagReplacer.addTag(TagStrings::studentMiddleName, "Wyatt");
    tagReplacer.addTag(TagStrings::studentLastName, "Earp");
    tagReplacer.addTag(TagStrings::studentHimselfHerself, "Him");
    qDebug() << QString::fromStdString(tagReplacer.performReplacement(testString));
}

#endif
