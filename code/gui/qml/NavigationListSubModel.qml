import QtQuick 2.0
import "pageCreator.js" as PageCreator
import "utilities.js" as JsUtil
import CppEnums 1.0

Rectangle {
    id: wrapper
    anchors.fill: parent
    property var model
    property var modelType

    clip: true

    ListView {
        id: listOfItems

        height: parent.height
        width: parent.width - listOperationsContainer.width - (scrollbar.width + 5)
        model: wrapper.model

        highlight: Rectangle {
            width: listOfItems.width
            color: "lightsteelblue"
        }

        onCountChanged: listOperationsContainer.fillListOperationsModel()

        delegate: NavigationListDelegate{
            model: wrapper.model
            modelType: wrapper.modelType
        }
    }

    Scrollbar {
        id: scrollbar
        target: listOfItems
    }

    PageOperationsContainer {
        id: listOperationsContainer
        anchors.left: scrollbar.right
        model: wrapper.model
        listOfItems: listOfItems
    }

    Component.onCompleted: {
        listOperationsContainer.fillListOperationsModel()
    }
}
