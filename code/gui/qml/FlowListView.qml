import QtQuick 2.0

Flickable {
    id: flowListView
    anchors.fill: parent

    contentWidth: parent.width;
    contentHeight: flow.childrenRect.height

    property alias count: repeater.count
    property int currentIndex: -1
    property variant currentItem;
    property alias delegate: repeater.delegate
    property alias flow: flow.flow
    property alias model: repeater.model
    property alias displaced: flow.move

    onCurrentIndexChanged: {
        currentItem = flowListView.currentIndex
    }

    Flow {
        id: flow
        width: parent.width
        spacing: 10

        Repeater {
            id: repeater

            onCountChanged: {
                if (flowListView.currentIndex === -1 && count > 0) {
                    flowListView.currentIndex = 0
                }
                if (flowListView.currentIndex >= count) {
                    flowListView.currentIndex = count - 1
                }
            }
        }
    }
}
