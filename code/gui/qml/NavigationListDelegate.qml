import QtQuick 2.0
import "pageCreator.js" as PageCreator
import ModelTypeEnums 1.0

Rectangle {
    id: wrapper
    height: 40
    width: parent.width

    property var model
    property var modelType

    readonly property string itemString: displayString

    color: ListView.isCurrentItem ? "#BBBBBB" : "#EEEEEE"
    state: "mouseOut"

    states: [
        State {
            name: "mouseIn"
            PropertyChanges { target: arrowButton; color: "#33AAEE" }
        },
        State {
            name: "mouseOut"
            PropertyChanges { target: arrowButton; color: "#AAAAAA" }
        },
        State {
            name: "pressed"
            when: arrowMouseArea.pressed
            PropertyChanges { target: arrowButton; color: "#33CCEE" }
        }
    ]

    MouseArea {
        anchors.fill: parent

        Rectangle {
            id: progressIndicator
            width: 5
            height: parent.height
            anchors.rightMargin: 5

            visible: (modelType === QGenericListModel.EvaluationList ||
                      modelType === QGenericListModel.EvalSetList)

            color: (modelType === QGenericListModel.EvaluationList ||
                    modelType === QGenericListModel.EvalSetList) ?
                       mapProgressIndicatorToColor(progressLevel) :
                       "transparent"
        }

        Text {
            anchors.verticalCenter: parent.verticalCenter
            anchors.left:  progressIndicator.right
            anchors.leftMargin: 5
            renderType: Text.NativeRendering
            text: displayString
        }

        MouseArea {
            id: arrowMouseArea
            height:20
            width: 20
            anchors.right: parent.right
            anchors.rightMargin: 5
            anchors.verticalCenter: parent.verticalCenter
            hoverEnabled: true

            Text {
                id: arrowButton
                text: "\uf061"
                font.family: fontAwesome.name
                font.pointSize: 16
            }

            onEntered: wrapper.state = "mouseIn"
            onExited: wrapper.state = "mouseOut"

            onClicked: {
                wrapper.state = "mouseOut"
                pageStack.push(PageCreator.createModelByType(wrapper.modelType,
                                                             wrapper.model.getNextPageFromIndex(index)))
            }
        }

        onClicked: wrapper.ListView.view.currentIndex = index
    }

    function mapProgressIndicatorToColor(progressLevel)
    {
        switch(progressLevel)
        {
        case 0:
            return "red"

        case 1:
            return "yellow"

        case 2:
            return "green"

        default:
            console.log("Error: progressLevel not expected: " + progressLevel)
            return "transparent"
        }
    }
}
