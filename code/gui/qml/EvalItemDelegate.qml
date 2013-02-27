import QtQuick 2.0

MouseArea {
    id: delegateRoot

    property int visualIndex: VisualDataModel.itemsIndex

    width: 120; height: 80
    drag.target: icon

    Rectangle {
        id: icon
        width: 115
        height: 75
        clip: true
        anchors {
            horizontalCenter: parent.horizontalCenter;
            verticalCenter: parent.verticalCenter
        }
        color: "lightgray"
        border.color: "black"
        radius: 3

        Drag.active: delegateRoot.drag.active
        Drag.source: delegateRoot
        Drag.hotSpot.x: 36
        Drag.hotSpot.y: 36

        Text {
            anchors.fill: parent

            text: evalItemString
            renderType: Text.NativeRendering
            wrapMode: Text.WordWrap
        }

        states: [
            State {
                when: icon.Drag.active
                ParentChange {
                    target: icon
                    parent: root
                }

                AnchorChanges {
                    target: icon;
                    anchors.horizontalCenter: undefined;
                    anchors.verticalCenter: undefined
                }
            }
        ]
    }

    DropArea {
        anchors { fill: parent; margins: 15 }

        onEntered: {
            evalModel.move(drag.source.visualIndex, delegateRoot.visualIndex)
        }
    }
}
