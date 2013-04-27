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
            return "#00EE00"
        case 2:
            return "yellow"
        case 3:
            return "#CCCC00"
        case 4:
            return "red"
        default:
            return "transparent"
    }
}
