#ifndef TAGSTRINGS_H
#define TAGSTRINGS_H

#include <string>
#include <unordered_map>

namespace TagStrings {

// these tags will all vary based on the contents of the object
const std::string studentFirstName = "<Student_First_Name>";
const std::string studentMiddleName = "<Student_Middle_Name>";
const std::string studentLastName = "<Student_Last_Name>";
const std::string studentFirstLastName = "<Student_First_Last_Name>";

// these will all have lookups based on gender
const std::string studentHeShe = "<Student_he_she>";
const std::string studentHisHer = "<Student_his_her>";
const std::string studentHimHer = "<Student_him_her>";
const std::string studentHimselfHerself = "<Student_himself_herself>";

}

#endif // TAGSTRINGS_H
