import QtQuick 2.0

ListView {
    property int numElementsVisible: 3

    height: numElementsVisible * (currentItem.height + spacing)
    width: (parent) ? parent.width : 0

    highlightMoveDuration: 1
    highlightResizeDuration: 1
    highlight: Rectangle {
        width: (parent) ? parent.width : 0
        color: "#EEEEEE"
    }
    spacing: 1
    anchors.margins: 5
}
