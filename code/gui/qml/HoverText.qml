import QtQuick 2.0

Item {
    property alias text: label.text
    height: label.height + 10
    width: label.width + 10

    visible: false

    Timer {
        interval: 1000
        running: true
        onTriggered: {
            parent.visible = true
            stop()
        }
    }

    Rectangle {
        anchors.fill: parent

        border.color: "#AAAAAA"
        color: "#333333"

        Text {
            id: label
            anchors.centerIn: parent

            renderType: Text.NativeRendering
            color: "white"
        }

    }

}
