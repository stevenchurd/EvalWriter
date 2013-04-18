import QtQuick 2.0

Item {
    property alias text: label.text
    height: label.height + 5
    width: label.width + 5

    visible: false
    Timer {
        interval: 2000
        running: true
        onTriggered: {
            parent.visible = true
            stop()
        }
    }

    Rectangle {
        anchors.fill: parent

        border.color: "black"
        color: "darkgray"

        Text {
            id: label
            anchors.centerIn: parent

            color: "black"
        }

    }

}
