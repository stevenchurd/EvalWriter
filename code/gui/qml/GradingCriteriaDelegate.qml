import QtQuick 2.0

Column {
    id: wrapper

    width: parent.width

    property alias areCIVisible: gcRow.expanded

    Connections {
        target: gcRow
        onExpandClicked: {
            gcRow.expanded = !gcRow.expanded
            wrapper.ListView.view.currentIndex = index
        }

        onDeleteClicked: { wrapper.ListView.view.model.removeGradingCriteria(index) }
        onHeaderClicked: { wrapper.ListView.view.currentIndex = index }
    }

    GradingCriteriaRow {
        id: gcRow
        text: gradingCriteriaString + " (" + numCriteriaItems + ")"
        buttonsVisible: wrapper.ListView.view.currentIndex === index
        expandable: numCriteriaItems > 0
    }

    Repeater {
        width: parent.width

        model: gradingCriteriaModel.criteriaItemModel(index)
        CriteriaItemRow {
            id: ciRow
            width: parent.width
            text: criteriaString
            criteriaLevelIndicator: criteriaLevel
            visible: areCIVisible
        }


    }
}
