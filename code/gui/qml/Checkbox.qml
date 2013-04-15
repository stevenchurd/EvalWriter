import QtQuick 2.0

Rectangle {
    id: wrapper

    signal checkToggled

    property bool initiallyChecked
    state: (initiallyChecked) ? "checked" : "unchecked"

    border.color: "black"
    clip: true

    Text {
        id: checkmark
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        font.pointSize: 10
        text:"\u2713"
        renderType: Text.NativeRendering
    }

    MouseArea {
        anchors.fill: parent
        onClicked: {
            if(wrapper.state == "checked")
                wrapper.state = "unchecked"
            else
                wrapper.state = "checked"

            checkToggled()
        }
    }

    states: [
        State {
            name: "checked"
            PropertyChanges { target: checkmark; visible: true }
        },
        State {
            name: "unchecked"
            PropertyChanges { target: checkmark; visible: false }
        }
    ]
}
