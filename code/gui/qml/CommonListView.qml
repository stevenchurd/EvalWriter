import QtQuick 2.0

Rectangle {
    property alias modelName: list.model
    property alias delegateName: list.delegate
    property alias highlight: list.highlight

    anchors.fill: parent

    ListView {
        anchors.fill: parent
        id: list
        focus: true
        highlight: Rectangle {
            color: "lightsteelblue"
            width: parent.width
        }
    }
}
