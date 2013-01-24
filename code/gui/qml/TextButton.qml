import QtQuick 2.0

Rectangle {
    id: container

    property alias text: label.text

    signal clicked

    width: label.width + 20; height: label.height + 6
    border.color: "gray"
    border.width: 1
    color: "transparent"

    MouseArea {
        id: mouseArea
        anchors.fill: parent
        onClicked: { container.clicked() }
        hoverEnabled: true
        onEntered: { container.color = "lightgray" }
        onExited: { container.color = "transparent" }
    }

    Text {
        id: label
        anchors.centerIn: parent
    }

    states: State {
        name: "pressed"
        when: mouseArea.pressed
        PropertyChanges { target: container; color: "darkgray" }
    }
}
