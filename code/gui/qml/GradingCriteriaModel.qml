import QtQuick 2.0

Item {
    id: wrapper

    property bool editable

    anchors.fill: parent
    anchors.margins: 5

    ListView {
        id: gradingCriteriaList

        height: parent.height
        width: parent.width - (scrollbar.width+5) - listOperationsContainer.width
        clip: true

        model: gradingCriteriaModel
        delegate: GradingCriteriaDelegate{ editable: wrapper.editable }
        spacing: 5
    }

    Scrollbar {
        id: scrollbar
        target: gradingCriteriaList
    }

    PageOperationsContainer {
        id: listOperationsContainer
        visible: editable
        anchors.left: scrollbar.right
        model: gradingCriteriaModel
        listOfItems: gradingCriteriaList
    }

    Component.onCompleted: listOperationsContainer.fillListOperationsModel()
}
