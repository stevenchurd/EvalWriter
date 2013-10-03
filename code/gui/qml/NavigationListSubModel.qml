import QtQuick 2.0
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
        spacing: 5

        displaced: Transition {
            NumberAnimation { properties: "x,y"; duration: 200 }
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
