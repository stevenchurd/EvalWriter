import QtQuick 2.0

Item {
    id: delegateItem

    property alias itemsToHold: container.children

    width: 100
    height: 50

    Rectangle {
        id: container

        anchors.fill: parent
        border.color: "black"
        color: "transparent"

        MouseArea {
            anchors.fill: parent
            onClicked: delegateItem.ListView.view.currentIndex = index
        }
    }
}


