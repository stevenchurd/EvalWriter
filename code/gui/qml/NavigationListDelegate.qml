import QtQuick 2.0
import "pageCreator.js" as PageCreator
import ModelTypeEnums 1.0
import CppEnums 1.0

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
            id: highlight
            width: 2
            height: parent.height
            color: "#33AAEE"
        }

        Text {
            id: listItemText
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: highlight.right
            anchors.leftMargin: 5
            anchors.rightMargin: 5
            renderType: Text.NativeRendering
            text: displayString
        }

        IconButton {
            id: progressIndicator
            height: parent.height

            anchors.leftMargin: 5
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: listItemText.right

            icon: "\uf058"
            pressableIcon: false

            hoverText: (modelType === QGenericListModel.EvaluationList ||
                        modelType === QGenericListModel.EvalSetList) ?
                           mapProgressIndicatorToHoverText(progressLevel) :
                           ""

            visible: (modelType === QGenericListModel.EvaluationList ||
                      modelType === QGenericListModel.EvalSetList)

            iconColor: (modelType === QGenericListModel.EvaluationList ||
                        modelType === QGenericListModel.EvalSetList) ?
                           mapProgressIndicatorToColor(progressLevel) :
                           "transparent"
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
                anchors.centerIn: parent
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
        case QEvalSetsListModel.EvalSetNew:
            return "red"

        case QEvalSetsListModel.EvalSetInProgress:
            return "yellow"

        case QEvalSetsListModel.EvalSetComplete:
            return "green"

        case QEvalSetsListModel.EvalSetEmpty:
            return "#888888"

        default:
            console.log("Error: progressLevel not expected: " + progressLevel)
            return "transparent"
        }
    }

    function mapProgressIndicatorToHoverText(progressLevel)
    {
        switch(progressLevel)
        {
        case QEvalSetsListModel.EvalSetNew:
            return "New"

        case QEvalSetsListModel.EvalSetInProgress:
            return "In Progress"

        case QEvalSetsListModel.EvalSetComplete:
            return "Complete"

        case QEvalSetsListModel.EvalSetEmpty:
            return "No evals added"

        default:
            console.log("Error: progressLevel not expected: " + progressLevel)
            return ""
        }
    }
}
