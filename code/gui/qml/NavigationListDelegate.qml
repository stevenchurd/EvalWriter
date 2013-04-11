import QtQuick 2.0
import "pageCreator.js" as PageCreator

MouseArea {
    id: wrapper
    height: 40
    width: parent.width

    property var model
    property var modelType

    readonly property string itemString: displayString

    Text {
        anchors.verticalCenter: parent.verticalCenter
        renderType: Text.NativeRendering
        text: displayString
    }

    Rectangle {
        height:20
        width: 20
        anchors.right: parent.right
        anchors.margins: 10
        anchors.verticalCenter: parent.verticalCenter
        color: "green"
        MouseArea {
            anchors.fill: parent

            onClicked: {
                pageStack.push(PageCreator.createModelByType(wrapper.modelType,
                                                             wrapper.model.getSubModelFromIndex(index)))
            }
        }
    }

    onClicked: wrapper.ListView.view.currentIndex = index
}
