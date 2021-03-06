import QtQuick 2.0

Rectangle {
    id: wrapper
    property bool editable
    property int itemSelected: -1
    property int gcIndex: index

    width: parent.width
    height: column.height + 5
    color: ListView.isCurrentItem ? "#BBBBBB" : "#EEEEEE"
    clip: true

    Behavior on height {
        NumberAnimation { duration: 100 }
    }

    Column {
        id: column

        width: parent.width

        Connections {
            target: gcRow
            onExpandClicked: {
                if(gcRow.expanded)
                {
                    wrapper.ListView.view.model.collapseRow(index)
                }
                else
                {
                    wrapper.ListView.view.model.expandRow(index)
                }
                wrapper.ListView.view.currentIndex = index
            }

            onHeaderClicked: {
                itemSelected = -1
                wrapper.ListView.view.currentIndex = index
            }
        }

        Rectangle {
            id: highlight
            width: parent.width
            height: 1
            color: wrapper.ListView.isCurrentItem ? "#33AAEE" : "transparent"
        }

        GradingCriteriaRow {
            id: gcRow
            text: gradingCriteriaString + " (" + numCriteriaItems + ")"
            buttonsVisible: wrapper.editable && wrapper.ListView.view.currentIndex === index
            editable: wrapper.editable
            expandable: numCriteriaItems > 0
            onExpandedChanged: { itemSelected = -1 }
            expanded: isExpanded
            model: wrapper.ListView.view.model
        }

        Repeater {
            width: parent.width

            model: wrapper.ListView.view.model.getCriteriaItemModel(index)
            delegate: CriteriaItemRow {
                width: parent.width
                text: criteriaString
                criteriaLevelValue: criteriaLevel
                visible: gcRow.expanded
                editable: wrapper.editable
                buttonsVisible: wrapper.editable && index === itemSelected
                isSelected: index === itemSelected
                model: wrapper.ListView.view.model.getCriteriaItemModel(gcIndex)

                Component.onCompleted: {
                    onItemClicked.connect(selectCriteriaItem)
                }
            }
        }
    }

    function selectCriteriaItem(sublistIndex)
    {
        wrapper.ListView.view.currentIndex = index
        itemSelected = (wrapper.ListView.view.currentIndex === index) ? (sublistIndex) : -1
    }

    onFocusChanged: { itemSelected = -1 }
}
