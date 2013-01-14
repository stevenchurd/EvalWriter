import QtQuick 2.0

Rectangle {
    Row {
        id: buttons
        anchors { left: parent.left; bottom: parent.bottom; margins: 20 }
        spacing: 10

        TextButton {
            text: "Delete"
        }

        TextButton {
            text: "Modify"
        }
    }

    width: 400
    height: 400
    border.color: "black"
}
