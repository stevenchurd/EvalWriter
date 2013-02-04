import QtQuick 2.0

Column {
    id: wrapper

    width: parent.width

    property int itemSelected: -1
    property int gcIndex: index

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

        onDeleteClicked: {
            wizardContent.sourceComponent = isDeleteGradingCriteriaOkDialog
            wizardContent.show()
        }
        onHeaderClicked: { wrapper.ListView.view.currentIndex = index }
    }

    GradingCriteriaRow {
        id: gcRow
        text: gradingCriteriaString + " (" + numCriteriaItems + ")"
        buttonsVisible: wrapper.ListView.view.currentIndex === index
        expandable: numCriteriaItems > 0
        onExpandedChanged: { itemSelected = -1 }
        expanded: isExpanded
    }

    Repeater {
        width: parent.width

        model: wrapper.ListView.view.model.criteriaItemModel(index)
        delegate: CriteriaItemRow {
            width: parent.width - 40
            text: criteriaString
            criteriaLevelIndicator: criteriaLevel
            visible: gcRow.expanded
            buttonsVisible: index === itemSelected
            model: wrapper.ListView.view.model.criteriaItemModel(gcIndex)

            Component.onCompleted: {
                onItemClicked.connect(selectCriteriaItem)
            }
      }
    }

    function selectCriteriaItem(sublistIndex)
    {
        wrapper.ListView.view.currentIndex = index
        itemSelected = (wrapper.ListView.view.currentIndex === index) ? (sublistIndex) : -1
    }

    function deleteGradingCriteria()
    {
        wrapper.ListView.view.model.removeGradingCriteria(index)
    }

    onFocusChanged: { itemSelected = -1 }


    // wizard component specifications
    Component {
        id: isDeleteGradingCriteriaOkDialog
        YesNoDialog {
            id: dialog
            dialogText: "Do you want to delete this item?\n\nIf you delete this item, all evaluations that use these\nelements will be converted to custom text items."

            Component.onCompleted:
            {
                dialog.onCanceled.connect(wizardContent.close)
                dialog.onNoClicked.connect(wizardContent.close)
                dialog.onYesClicked.connect(deleteGradingCriteria)
                dialog.onYesClicked.connect(wizardContent.close)
            }
        }
    }
}
