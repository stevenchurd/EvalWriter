import QtQuick 2.0

Item {
    anchors.fill: parent

    Item {
        id: leftColumn
        height: parent.height
        width: parent.width/3
        GradingCriteriaModel{}
    }

    Rectangle {
        height: parent.height
        width: 1
        border.color: "black"
    }

    Item {
        id: rightColumn
        height: parent.height
        width: parent.width/3 * 2
        anchors.left: leftColumn.right
        EvalModel{}
    }
}
