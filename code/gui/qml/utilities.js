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


function getOperationString(operation)
{
    switch(operation) {
        case QCoursesListModel.AddCourse:
            return "Add New Course"

        case QCoursesListModel.RemoveCourse:
            return "Delete Course"

        case QEvalSetsListModel.AddEvalSet:
            return "Add Evaluation Set"

        default:
            return "Error: operation not matched"
    }
}
