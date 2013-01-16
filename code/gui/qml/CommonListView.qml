import QtQuick 2.0

Rectangle {
    property alias modelName: list.model
    property alias delegateName: list.delegate
    property alias highlight: list.highlight

    anchors.fill: parent

    ListView {
        id: list

        anchors.fill: parent
        focus: true
        highlight: Rectangle {
            color: "lightsteelblue"
        }
    }
}
