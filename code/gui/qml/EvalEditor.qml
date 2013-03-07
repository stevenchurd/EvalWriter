import QtQuick 2.0

Item {
    anchors.fill: parent

    Item {
        id: leftColumn
        height: parent.height
        width: parent.width/3
        GradingCriteriaModel{}
    }

    Item {
        id: rightColumn
        height: parent.height
        width: parent.width/3 * 2
        anchors.left: leftColumn.right
        EvalModel{}
    }
}
