import QtQuick 2.0

Item {
    id: delegateItem
    property alias text: textItem.text
    height: textItem.height

    width: parent.width
    Rectangle {
        id: highlight
        height: parent.height
        width: 2
        visible: delegateItem.ListView.isCurrentItem
        color: "#33AAEE"
    }

    Text {
        id: textItem
        anchors.left: highlight.right
        anchors.leftMargin: 5

        font.pointSize: 10
        renderType: Text.NativeRendering
    }

    MouseArea {
        anchors.fill: parent
        onClicked: delegateItem.ListView.view.currentIndex = index
    }
}


