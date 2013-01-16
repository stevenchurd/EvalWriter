import QtQuick 2.0

Component {
    id: cld

    Item {
        id: courseItem

        width: 100
        height: 50

        Rectangle {

            anchors.fill: parent
            border.color: "black"
            color: "transparent"

            Text {
                text: name
                renderType: Text.NativeRendering
            }

            MouseArea {
                anchors.fill: parent
                onClicked: courseItem.ListView.view.currentIndex = index
            }
        }
    }
}


