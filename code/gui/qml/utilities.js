Qt.include("MainNavigationModel.qml")

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

function isListModelType(modelType)
{
    switch(modelType)
    {
        case 1: //StudentList
        case 2: //EvaluationList
        case 3: //CourseList
        case 4: //EvalSetList
            return true

        case 5: //GradingCriteria
            return false
    }
}


function getOperationString(operation)
{
    switch(operation) {
        case QCoursesListModel.AddCourse:
            return "Add New Course"

        case QCoursesListModel.RemoveCourse:
            return "Delete Course"

        default:
            return "Error: operation not matched"
    }
}
