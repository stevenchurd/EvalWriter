import QtQuick 2.0
import "hoverTextCreator.js" as HoverText

Rectangle {
    id: container

    property alias icon: label.text
    property alias size: label.font.pointSize
    property string hoverText

    property bool pressableIcon: true
    property color iconColor: "#555555"
    property color hoverColor: "#33AAEE"
    property color pressedColor: "#33CCEE"

    signal clicked

    width: label.width + 10
    height: label.height + 5
    color: "transparent"
    clip: true

    MouseArea {
        id: mouseArea
        anchors.fill: parent
        hoverEnabled: true

        onEntered: {
            if(pressableIcon)
                container.state = "mouseIn"
        }

        onExited: {
            if(pressableIcon)
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
        smooth: true
        font.family: fontAwesome.name
        font.pointSize: 14
        wrapMode: Text.WordWrap
        color: iconColor
    }

    states: [
        State {
            name: "mouseIn"
            PropertyChanges { target: label; color: hoverColor }
        },
        State {
            name: "mouseOut"
            PropertyChanges { target: label; color: iconColor }
        },
        State {
            name: "pressed"
            when: pressableIcon && mouseArea.pressed
            PropertyChanges { target: label; color: pressedColor}
        }
    ]
}
