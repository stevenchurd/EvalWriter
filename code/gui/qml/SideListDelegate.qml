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
        x: parent.x - width/3
        font.pointSize: 28
        font.family: fontAwesome.name
        text: mapSubModelTypeToIcon(submodelType)
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
                return "\uf0c0"

            case QGenericListModel.EvaluationList:
                return "\uf044"

            case QGenericListModel.CourseList:
                return "\uf02d"

            case QGenericListModel.EvalSetList:
                return "\uf08d"

            case QGenericListModel.GradingCriteria:
                return "\uf046"

            default:
                break;
        }
    }
}
