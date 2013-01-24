import QtQuick 2.0

ListView {
    id: list

    anchors.fill: parent
    focus: true
    highlightMoveDuration: 1
    highlightResizeDuration: 1
    highlight: Rectangle {
        width: parent.width
        color: "lightsteelblue"
    }
}
