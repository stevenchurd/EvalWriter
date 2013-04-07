Qt.include("MainNavigationModel.qml")
Qt.include("NavigationListSubModel.qml")

function getEvalItemColor(level) {
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

        default:
            console.log("Error: operation not defined: " + operation)
            return String(operation)
    }
}
