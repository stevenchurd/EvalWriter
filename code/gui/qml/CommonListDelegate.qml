import QtQuick 2.0

Item {
    id: delegateItem

    property alias itemsToHold: container.sourceComponent
    height: container.height
    width: parent.width

    Loader {
        id: container
    }

    MouseArea {
        anchors.fill: parent
        onClicked: delegateItem.ListView.view.currentIndex = index
    }
}


