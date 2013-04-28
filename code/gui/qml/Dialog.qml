import QtQuick 2.0

Rectangle {
    id: wrapper

    property alias source: dialogContent.source
    property alias sourceComponent: dialogContent.sourceComponent

    signal canceled

    anchors.centerIn: parent
    height: dialogContent.height + dialogHeader.height + 10
    width: dialogContent.width + 30

    color: "#AAAAAA"
    border.color: "#EEEEEE"

    Rectangle {
        id: highlight
        width: 2
        height: parent.height - (parent.border.width*2)
        anchors.verticalCenter: parent.verticalCenter
        color: "#33AAEE"
    }

    Rectangle {
        id: dialogHeader

        width: wrapper.width
        height: cancelButton.height
        color: "transparent"
        anchors.top: parent.top

        IconButton {
            id: cancelButton
            icon: "\uf00d"
            onClicked: canceled()
            anchors.top: parent.top
            anchors.right: parent.right
        }
    }

    Loader {
        id: dialogContent
        anchors.top: dialogHeader.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        focus: true
    }
}
