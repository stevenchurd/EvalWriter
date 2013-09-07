#ifndef _GLOBALENUMS_H_
#define _GLOBALENUMS_H_

namespace ModelOperationRanges {
enum SubModelOperationRanges {
    InvalidOperation = 0,

    // CoursesList operations (1-10)
    CoursesListOperationsBegin = 1,
    CoursesListOperationsEnd = 10,

    // StudentsList operations (11-20)
    StudentsListOperationsBegin = 11,
    StudentsListOperationsEnd = 20,

    // EvalsList operations (21-30)
    EvalsListOperationsBegin = 21,
    EvalsListOperationsEnd = 30,

    // EvalSetsList operations (31-40)
    EvalSetsListOperationsBegin = 31,
    EvalSetsListOperationsEnd = 40,

    // Grading Griteria operations (41-50)
    GradingCriteriaListOperationsBegin = 41,
    GradingCriteriaListOperationsEnd = 50,

    // Evaluation operations (51-60)
    EvaluationOperationsBegin = 51,
    EvaluationOperationsEnd = 60
};

typedef SubModelOperationRanges ModelOperationEnum;
}


#endif
