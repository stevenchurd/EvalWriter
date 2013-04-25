import QtQuick 2.0
import "hoverTextCreator.js" as HoverText

Rectangle {
    id: container

    property alias icon: label.text
    property alias size: label.font.pointSize
    property string hoverText

    signal clicked

    width: label.width + 10
    height: label.height + 5
    color: "transparent"
    clip: true

    MouseArea {
        id: mouseArea
        anchors.fill: parent
        hoverEnabled: true

        onEntered: { container.state = "mouseIn" }

        onExited: {
            container.state = "mouseOut"
            if(hoverText.length > 0)
                HoverText.destroyHoverText()
        }
        onPositionChanged: {
            if(hoverText.length > 0)
                HoverText.createHoverText(mouse, hoverText, container)
        }

        onClicked: { container.clicked() }
    }

    Text {
        id: label
        anchors.centerIn: parent
        renderType: Text.NativeRendering
        font.family: fontAwesome.name
        font.pointSize: 14
        wrapMode: Text.WordWrap
    }

    states: [
        State {
            name: "mouseIn"
            PropertyChanges { target: label; color: "#33AAEE" }
        },
        State {
            name: "mouseOut"
            PropertyChanges { target: label; color: "black" }
        },
        State {
            name: "pressed"
            when: mouseArea.pressed
            PropertyChanges { target: label; color: "#33CCEE" }
        }
    ]
}
