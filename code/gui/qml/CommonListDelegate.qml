import QtQuick 2.0

Rectangle {
    id: delegateItem
    property alias text: textItem.text
    height: textItem.height
    width: parent.width
    color: "#999999"

    Rectangle {
        id: highlight
        anchors.left: parent.left
        height: parent.height
        width: parent.width
        visible: delegateItem.ListView.isCurrentItem
        color: "#111111"
    }

    Text {
        id: textItem
        anchors.left: parent.left
        anchors.leftMargin: 5
        color: "#DDDDDD"

        font.pointSize: 12
        renderType: Text.NativeRendering
    }

    Text {
        id: checkmark
        anchors.right: parent.right
        anchors.rightMargin: 5
        color: "#DDDDDD"
        font.pointSize: 12
        font.family: fontAwesome.name
        visible: delegateItem.ListView.isCurrentItem
        text: "\uF00C"
    }

    MouseArea {
        anchors.fill: parent
        onClicked: delegateItem.ListView.view.currentIndex = index
    }
}


