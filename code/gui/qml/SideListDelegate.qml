import QtQuick 2.0

MouseArea {
    id: wrapper
    property string myText: submodelName

    anchors.horizontalCenter: parent.horizontalCenter
    width: parent.width
    height: 45

    Rectangle {
        anchors.left: wrapper.left
        height: parent.height
        width: 2

        color: "#33AAEE"
    }

    Text {
        anchors.verticalCenter:  parent.verticalCenter
        anchors.left: parent.left
        anchors.leftMargin: 10
        font.pointSize: 14
        renderType: Text.NativeRendering
        text: submodelName
        //color: (wrapper.ListView.isCurrentItem) ? "#EEEEEE" : "black"
    }

    onClicked: {
        wrapper.ListView.view.currentIndex = index
    }
}
