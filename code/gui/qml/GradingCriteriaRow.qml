import QtQuick 2.0

Rectangle {
    id: decorativeRect

    property alias text: gradingCriteriaText.text
    property bool buttonsVisible
    property bool expandable
    property bool expanded

    signal expandClicked
    signal addClicked
    signal deleteClicked
    signal modifyClicked

    width: parent.width - 50
    height: gradingCriteriaText.height + 10
    anchors.horizontalCenter: parent.horizontalCenter
    color: "transparent"

    Row {
        id: rowContainer

        width: parent.width
        spacing: 10

        Image {
            id: openArrow

            anchors.verticalCenter: parent.verticalCenter
            source: { (expanded) ? "qrc:Files/arrowdown.png" : "qrc:Files/arrowright.png" }
            opacity: { (expandable) ? 1 : 0 }

            MouseArea {
                anchors.fill: parent
                onClicked: expandClicked()
                enabled: { (expandable) ? 1: 0 }
            }
        }

        Text {
            id: gradingCriteriaText
            width: {parent.width - openArrow.width - addButton.width - modifyButton.width - deleteButton.width - (rowContainer.spacing*4)}

            font.pointSize: 16
            wrapMode: Text.WordWrap
        }

        TextButton {
            id: addButton
            text: "Add Item"
            anchors.top: parent.top
            visible: buttonsVisible
            onClicked: addClicked()
        }

        TextButton {
            id: modifyButton
            text: "Modify"
            anchors.top: parent.top
            visible: buttonsVisible
            onClicked: modifyClicked()
        }

        TextButton {
            id: deleteButton
            text: "Delete"
            anchors.top: parent.top
            visible: buttonsVisible
            onClicked: deleteClicked()
        }
    }
}
