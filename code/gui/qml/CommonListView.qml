import QtQuick 2.0

ListView {
    highlightMoveDuration: 1
    highlightResizeDuration: 1
    highlight: Rectangle {
        width: parent.width
        color: "#EEEEEE"
    }
    spacing: 5
    anchors.margins: 5
}
