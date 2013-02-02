import QtQuick 2.0

Column {
    id: wrapper

    width: parent.width

    property int itemSelected: -1

    Connections {
        target: gcRow
        onExpandClicked: {
            gcRow.expanded = (gcRow.expanded) ? false : true
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
        onExpandedChanged: { itemSelected = -1 }
    }

    Repeater {
        id: repeaterItem

        width: parent.width

        model: gradingCriteriaModel.criteriaItemModel(index)
        delegate: CriteriaItemRow {
            width: parent.width - 40
            text: criteriaString
            criteriaLevelIndicator: criteriaLevel
            visible: gcRow.expanded
            buttonsVisible: index === itemSelected

            Component.onCompleted: onItemClicked.connect(selectItem)
        }
    }

    function selectItem(sublistIndex)
    {
        wrapper.ListView.view.currentIndex = index
        itemSelected = (wrapper.ListView.view.currentIndex === index) ? (sublistIndex) : -1
    }

    onFocusChanged: { itemSelected = -1 }
}
