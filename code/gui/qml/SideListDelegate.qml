import QtQuick 2.0
import ModelTypeEnums 1.0

MouseArea {
    id: wrapper

    anchors.horizontalCenter: parent.horizontalCenter
    width: parent.width
    height: 45

    Text {
        id: typeIcon
        anchors.verticalCenter:  parent.verticalCenter
        x: parent.x - width/2
        font.pointSize: 28
        font.family: fontAwesome.name
        renderType: Text.NativeRendering
        text: mapSubModelTypeToIcon(submodelType)
        color: "#888888"
    }

    Rectangle {
        id: hightlight
        anchors.left: wrapper.left
        height: parent.height
        width: 2

        color: "#33AAEE"
    }

    Text {
        anchors.verticalCenter:  parent.verticalCenter
        anchors.left: typeIcon.right
        anchors.leftMargin: 5
        font.pointSize: 14
        renderType: Text.NativeRendering
        text: submodelName
        //color: (wrapper.ListView.isCurrentItem) ? "#EEEEEE" : "black"
    }

    onClicked: {
        wrapper.ListView.view.currentIndex = index
    }

    function mapSubModelTypeToIcon(submodelType)
    {
        switch(submodelType)
        {
            case QGenericListModel.StudentList:
                return "\uf001"

            case QGenericListModel.EvaluationList:
                return "\uf002"

            case QGenericListModel.CourseList:
                return "\uf02d"

            case QGenericListModel.EvalSetList:
                return "\uf004"

            case QGenericListModel.GradingCriteria:
                return "\uf004"

            default:
                break;
        }
    }
}
