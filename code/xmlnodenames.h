#ifndef XMLNODENAMES_H
#define XMLNODENAMES_H

//global strings
const std::string separator(".");
const std::string elementNameNode("name");
const std::string elementValueNode("value");


// root nodes
const std::string coursesRootNode("CoursesRoot");
const std::string gradingCriteriaRootNode("GradingCriteriaRoot");
const std::string studentRootNode("StudentsRoot");


// course nodes
const std::string singleCourseNode("course");


// students nodes
const std::string studentFirstNameNode("firstName");
const std::string studentMiddleNameNode("middleName");
const std::string studentLastNameNode("lastName");
const std::string studentCoursesNode("Courses");
const std::string studentEvalsNode("Evals");
const std::string singleStudentNode("student");


// eval nodes
const std::string singleEvalNode("eval");



// grading criteria nodes
const std::string singleGradingCriteriaNode("gradingCriteria");


// criteria item nodes
const std::string criteriaItemLevelNode("level");
const std::string singleCriteriaItemNode("criteriaItem");
const std::string criteriaItemParentItemNode("parentItem");


// other nodes
const std::string customTextItemNode("customTextItemNode");

#endif // XMLNODENAMES_H
