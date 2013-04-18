import QtQuick 2.0
import "hoverTextCreator.js" as HoverText

Text {
    id: titleText
    anchors.verticalCenter: parent.verticalCenter
    state: "mouseOut"

    // TODO: do something if the list goes off the screen
    font.pointSize: (index === 0) ? 24 : 16
    font.family: (index === 0) ? fontAwesome.name : ""
    text: (index === 0) ? " \uf015" : " / " + title

    MouseArea {
        id: mouseArea
        anchors.fill: parent
        onClicked: pageStack.popTo(index)
        hoverEnabled: true

        onEntered: {
            titleText.state = "mouseIn"
        }
        onPositionChanged: {
            HoverText.createHoverText(mouse, title)
        }
        onExited: {
            titleText.state = "mouseOut"
            HoverText.destroyHoverText()
        }
    }


    states: [
        State {
            name: "mouseIn"
            PropertyChanges { target: titleText; color: "#33AAEE" }
        },
        State {
            name: "mouseOut"
            PropertyChanges { target: titleText; color: "black" }
        },
        State {
            name: "pressed"
            when: mouseArea.pressed
            PropertyChanges { target: titleText; color: "#33CCEE" }
        }

    ]
}
