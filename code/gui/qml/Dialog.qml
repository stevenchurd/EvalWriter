import QtQuick 2.0

Rectangle {
    property alias source: dialogContent.source
    property alias sourceComponent: dialogContent.sourceComponent

    signal canceled

    anchors.centerIn: parent
    height: dialogContent.height
    width: dialogContent.width

    border.color: "black"
    radius: 3
    antialiasing: true

    Column {
        Rectangle {
            id: dialogHeader

            width: dialogContent.width
            height: cancelButton.height

            color: "lightblue"
            radius: 3
            antialiasing: true

            TextButton {
                id: cancelButton
                text: "X"
                onClicked: canceled()
                anchors.top: parent.top
                anchors.right: parent.right
            }
        }

        Rectangle {
            width: dialogContent.width
            height: 1

            border.color: "lightgray"
        }

        Loader {
            id: dialogContent

        }
    }
}
