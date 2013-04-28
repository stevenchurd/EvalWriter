import QtQuick 2.0

Rectangle {
    id: container

    property alias text: label.text

    signal clicked

    width: label.width + 20
    height: label.height + 6
    state: "mouseOut"
    clip: true

    Rectangle {
        id: highlight
        color: "#33AAEE"
        height: parent.height
        width: 2
    }

    MouseArea {
        id: mouseArea
        anchors.fill: parent
        onClicked: {
            container.clicked()
            container.state = "mouseOut"
        }
        hoverEnabled: true
        onEntered: container.state = "mouseIn"
        onExited: container.state = "mouseOut"
    }

    Text {
        id: label
        anchors.centerIn: parent
        renderType: Text.NativeRendering
        wrapMode: Text.WordWrap
        color: "#EEEEEE"
    }

    states: [
        State {
            name: "pressed"
            when: mouseArea.pressed
            PropertyChanges { target: container; color: "#555555" }
            PropertyChanges { target: highlight; color: "#33CCEE" }
        },
        State {
            name: "mouseIn"
            PropertyChanges { target: container; color: "#444444" }
            PropertyChanges { target: highlight; color: "#33CCEE" }
        },
        State {
            name: "mouseOut"
            PropertyChanges { target: container; color: "#666666" }
            PropertyChanges { target: highlight; color: "#33AAEE" }
        }
    ]
}
