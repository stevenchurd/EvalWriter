Qt.include("MainNavigationModel.qml")
Qt.include("NavigationListSubModel.qml")
Qt.include("PageOperationsContainer.qml")
Qt.include("GradingCriteriaModel.qml")

function getEvalItemColor(level)
{
    switch(level)
    {
        case 0:
            return "green"
        case 1:
            return "lightgreen"
        case 2:
            return "yellow"
        case 3:
            return "#ff6666"
        case 4:
            return "red"
        default:
            return "transparent"
    }
}


function getOperationString(operation)
{
    switch(operation) {
        // Course List operations
        case QCoursesListModel.AddCourse:
            return "Add New Class"

        case QCoursesListModel.RemoveCourse:
            return "Delete Class"

        case QCoursesListModel.RenameCourse:
            return "Rename Class"

        case QCoursesListModel.RemoveExistingCourseFromStudent:
            return "Remove Student from Class"

        case QCoursesListModel.AddExistingCourseToStudent:
            return "Add Student to Class"


        // Eval Set List Operations
        case QEvalSetsListModel.AddEvalSet:
            return "Add Evaluation Set"

        case QEvalSetsListModel.RemoveEvalSet:
            return "Remove Evaluation Set"

        case QEvalSetsListModel.RenameEvalSet:
            return "Rename Evaluation Set"


        // Student List Operations
        case QStudentsListModel.AddStudent:
            return "Add Student"

        case QStudentsListModel.RemoveStudent:
            return "Remove Student"

        case QStudentsListModel.RenameStudent:
            return "Rename Student"

        case QStudentsListModel.AddExistingStudentToCourse:
            return "Add Existing Student"

        case QStudentsListModel.RemoveStudentFromCourse:
            return "Remove Student from Class"


        // Eval List Operations
        case QEvalsListModel.AddEval:
            return "Add Evaluation"

        case QEvalsListModel.RemoveEval:
            return "Remove Evalutation"

        case QEvalsListModel.RenameEval:
            return "Rename Evaluation"

        case QEvalsListModel.AddExistingEvalToEvalSet:
            return "Add Existing Evaluation"

        case QEvalsListModel.RemoveEvalFromEvalSet:
            return "Remove Evaluation from Set"


        // Grading Category Operations
        case QGradingCriteriaModel.AddGradingCriteria:
            return "Add Grading Category"

        default:
            console.log("Error: operation not defined: " + operation)
            return String(operation)
    }
}


function isOperationIndexDependent(operation)
{
    switch(operation) {
        // Course List operations
        case QCoursesListModel.AddCourse:
            return false

        case QCoursesListModel.RemoveCourse:
            return true

        case QCoursesListModel.RenameCourse:
            return true

        case QCoursesListModel.RemoveExistingCourseFromStudent:
            return true

        case QCoursesListModel.AddExistingCourseToStudent:
            return false


        // Eval Set List Operations
        case QEvalSetsListModel.AddEvalSet:
            return false

        case QEvalSetsListModel.RemoveEvalSet:
            return true

        case QEvalSetsListModel.RenameEvalSet:
            return true


        // Student List Operations
        case QStudentsListModel.AddStudent:
            return false

        case QStudentsListModel.RemoveStudent:
            return true

        case QStudentsListModel.RenameStudent:
            return true

        case QStudentsListModel.AddExistingStudentToCourse:
            return false

        case QStudentsListModel.RemoveStudentFromCourse:
            return true


        // Eval List Operations
        case QEvalsListModel.AddEval:
            return false

        case QEvalsListModel.RemoveEval:
            return true

        case QEvalsListModel.RenameEval:
            return true

        case QEvalsListModel.AddExistingEvalToEvalSet:
            return false

        case QEvalsListModel.RemoveEvalFromEvalSet:
            return true


        // Grading Category Operations
        case QGradingCriteriaModel.AddGradingCriteria:
            return false

        default:
            console.log("Error: operation not defined: " + operation)
            return false
    }
}
