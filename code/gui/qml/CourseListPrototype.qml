import QtQuick 2.0

Rectangle {
    width: 400
    height: 400

    Item {
        id:listContainer
        height: 150
        width: 200

        ListView {
            id: clv
            model: courseModel
            delegate: CommonListDelegate{ itemsToHold: CourseListDelegateItem{} }
        }
    }

    Rectangle {
        id: hiddenRectangle
        height: 50
        width: 200
        color: "red"
        anchors.top: listContainer.bottom
        visible: false
    }

    TextButton {
        text: "Add"
        anchors.bottom: parent.bottom
        onClicked: {
            hiddenRectangle.visible = true
            clv.focus = false
            hiddenRectangle.focus = true
            clv.highlight = "red"
        }
    }
}



