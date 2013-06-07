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

    SearchBox {
        id: searchBox
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.margins: 2

        height: 25
        activeWidth: 300

        onTextChanged: model.setFilterFixedString(newText)
    }

    ListView {
        id: listOfItems

        anchors.top: searchBox.bottom
        anchors.margins: 2
        height: parent.height - searchBox.height
        width: parent.width - listOperationsContainer.width - (scrollbar.width + 5)
        model: wrapper.model
        spacing: 5
        clip: true

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
