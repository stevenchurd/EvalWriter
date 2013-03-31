import QtQuick 2.0
import "pageCreator.js" as PageCreator

Rectangle {
    id: wrapper
    anchors.fill: parent
    property var model
    property var modelType

    clip: true

    ListView {
        anchors.fill: parent
        model: wrapper.model

        highlight: Rectangle {
            width: parent.width
            color: "lightsteelblue"
        }

        delegate: MouseArea {
            id: delegateWrapper
            height: 60
            width: parent.width

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
            onClicked: delegateWrapper.ListView.view.currentIndex = index
        }
    }
}
