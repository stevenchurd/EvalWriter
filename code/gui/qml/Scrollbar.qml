import QtQuick 2.0

Rectangle {
    id: scrollBar
    property variant target

    clip: true
    color: "#DDDDDD"
    width: 10

    anchors.top: target.top
    anchors.bottom: target.bottom
    anchors.left: target.right
    anchors.topMargin: 5
    anchors.bottomMargin: 5
    anchors.leftMargin: 5

    //visible: (track.height == slider.height) ? false : true //TODO: !visible -> width: 0 (but creates a binding loop)


    states: [
        State { name: "nothing"; },
        State { name: "disabled"; when: track.height == slider.height }
    ]
    transitions: [
        Transition { to: "disabled"; //reversible: true;
            SequentialAnimation {
                NumberAnimation { target: scrollBar; property: "opacity"; to: 0; duration: 500; }
                PropertyAction { target: scrollBar; property: "visible"; value: false; }
            }
        },
        Transition { to: "*";
            PropertyAction { target: scrollBar; property: "visible"; value: true; }
            NumberAnimation { target: scrollBar; property: "opacity"; to: 1; duration: 500; }
        }
    ]

    Timer {
        property int scrollAmount

        id: timer
        repeat: true
        interval: 20
        onTriggered: {
            target.contentY = Math.max(0, Math.min(target.contentY + scrollAmount,
                                          target.contentHeight - target.height));
        }
    }

    Item {
        id: track
        anchors.top: parent.top
        anchors.bottom: parent.bottom;
        width: parent.width

        MouseArea {
            anchors.fill: parent
            onPressed: {
                timer.scrollAmount = target.height * (mouseY < slider.y ? -1 : 1) // scroll by a page
                timer.running = true;
            }
            onReleased: {
                timer.running = false;
            }
        }

        Rectangle {
            id:slider
            width: parent.width
            state: "mouseOut"

            anchors.bottom: (target.visibleArea.yPosition > 1)? parent.bottom: undefined
            height: {
                if (target.visibleArea.yPosition<0)         // Oberer Rand
                    Math.max(30, Math.min(target.height / target.contentHeight * track.height, track.height-y) +target.height * target.visibleArea.yPosition)
                else                                        // Mittelbereich
                    Math.min(target.height / target.contentHeight * track.height, track.height-y)
                }
            y: Math.max(0,Math.min(track.height-30, target.visibleArea.yPosition * track.height));

            MouseArea {
                id: sliderArea
                anchors.fill: parent
                drag.target: parent
                drag.axis: Drag.YAxis
                drag.minimumY: 0
                drag.maximumY: track.height - height
                hoverEnabled: true

                onPositionChanged: {
                    if (pressedButtons == Qt.LeftButton) {
                        target.contentY = slider.y * target.contentHeight / track.height
                    }
                }
                onEntered: slider.state = "mouseIn"
                onExited: slider.state = "mouseOut"
            }

            states: [
                State {
                    name: "mouseOut"
                    PropertyChanges { target: slider; color: "#555555" }
                },
                State {
                    name: "mouseIn"
                    PropertyChanges { target: slider; color: "#444444" }
                },
                State {
                    when: sliderArea.pressed
                    name: "pressed"
                    PropertyChanges { target: slider; color: "#555555" }
                }
            ]
        }
    }

}
