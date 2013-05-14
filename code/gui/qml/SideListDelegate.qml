import QtQuick 2.0
import ModelTypeEnums 1.0

MouseArea {
    id: wrapper

    anchors.horizontalCenter: parent.horizontalCenter
    width: parent.width
    height: 45
    hoverEnabled: true
    state: "mouseOut"

    Rectangle {
        id: highlight
        anchors.left: wrapper.left
        height: parent.height
        width: 2
        color: "#33AAEE"
    }

    Text {
        id: typeIcon
        anchors.verticalCenter:  parent.verticalCenter
        anchors.left: highlight.right
        anchors.leftMargin: 5
        font.pointSize: 14
        font.family: fontAwesome.name
        text: mapSubModelTypeToIcon(submodelType)
    }

    Text {
        id: listText
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

    onEntered: wrapper.state = "mouseIn"
    onExited: wrapper.state = "mouseOut"

    states: [
        State {
            name: "mouseIn"
            PropertyChanges { target: typeIcon; color: "#33AAEE" }
            PropertyChanges { target: listText; color: "#33AAEE" }
        },
        State {
            name: "mouseOut"
            PropertyChanges { target: typeIcon; color: "black" }
            PropertyChanges { target: listText; color: "black" }
        },
        State {
            name: "pressed"
            when: wrapper.pressed
            PropertyChanges { target: typeIcon; color: "#33CCEE" }
            PropertyChanges { target: listText; color: "#33CCEE" }
        }
    ]

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
