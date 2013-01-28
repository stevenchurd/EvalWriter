import QtQuick 2.0

Rectangle {
    id: screenContainer

    anchors.fill: parent

    CommonListView {
        id: treeView

        anchors.fill: parent

        delegate: TreeViewDelegate{}
        model: gradingCriteriaModel
    }
    Scrollbar {
        target: treeView
    }
}
