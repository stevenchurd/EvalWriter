import QtQuick 2.0

Rectangle {
    id: wrapper

    property alias source: dialogContent.source
    property alias sourceComponent: dialogContent.sourceComponent

    signal canceled

    anchors.centerIn: parent
    height: dialogContent.height + dialogHeader.height + 30
    width: dialogContent.width + 30

    border.color: "black"
    antialiasing: true

    Rectangle {
        id: dialogHeader

        width: wrapper.width
        height: cancelButton.height
        color: "transparent"
        anchors.top: parent.top

        TextButton {
            id: cancelButton
            text: "X"
            onClicked: canceled()
            anchors.top: parent.top
            anchors.right: parent.right
        }
    }

    Loader {
        id: dialogContent
        anchors.centerIn: parent
        focus: true
    }
}
