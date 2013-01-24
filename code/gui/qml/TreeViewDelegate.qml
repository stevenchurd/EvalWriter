import QtQuick 2.0

Item {
    id: wrapper

    width: parent.width
    height: (isGradingCriteria) ? gcRow.height : ciRow.height

    MouseArea {
        anchors.fill: parent
        onClicked: wrapper.ListView.view.currentIndex = index
    }

    Connections {
        target: gcRow
        onExpandClicked: {
            if(isOpened)
            {
                wrapper.ListView.view.model.closeItem(index)
                wrapper.ListView.view.currentIndex = index
            }
            else
            {
                wrapper.ListView.view.model.openItem(index)
                wrapper.ListView.view.currentIndex = index
            }
        }

        onDeleteClicked: { wrapper.ListView.view.model.removeGradingCriteria(index) }
    }

    Connections {
        target: ciRow

        onDeleteClicked: { wrapper.ListView.view.model.removeCriteriaItem(index) }
    }

    GradingCriteriaRow {
        id: gcRow
        text: string + " (" + numChildren + ")"
        buttonsVisible: wrapper.ListView.view.currentIndex === index
        expandable: hasChildren
        visible: isGradingCriteria
        expanded: isOpened
    }

    CriteriaItemRow {
        id: ciRow
        text: string
        buttonsVisible: wrapper.ListView.view.currentIndex === index
        visible: isGradingCriteria === false
        criteriaLevelIndicator: criteriaLevel
    }
}
