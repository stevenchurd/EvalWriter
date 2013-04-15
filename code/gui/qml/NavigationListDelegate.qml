import QtQuick 2.0
import "pageCreator.js" as PageCreator
import ModelTypeEnums 1.0

MouseArea {
    id: wrapper
    height: 40
    width: parent.width

    property var model
    property var modelType

    readonly property string itemString: displayString

    Rectangle {
        id: progressIndicator
        width: 5
        height: parent.height
        anchors.rightMargin: 5

        visible: (modelType === QGenericListModel.EvaluationList ||
                  modelType === QGenericListModel.EvalSetList)

        color: (modelType === QGenericListModel.EvaluationList ||
                modelType === QGenericListModel.EvalSetList) ?
                   mapProgressIndicatorToColor(wrapper.model.getProgressIndicator(index)) :
                   "transparent"
    }

    Text {
        anchors.verticalCenter: parent.verticalCenter
        anchors.left:  progressIndicator.right
        anchors.leftMargin: 5
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
                                                             wrapper.model.getNextPageFromIndex(index)))
            }
        }
    }

    onClicked: wrapper.ListView.view.currentIndex = index

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
