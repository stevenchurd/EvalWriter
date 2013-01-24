import QtQuick 2.0

Rectangle {
    width: 500
    height: 500

    Rectangle {
        id: screenContainer

        anchors.fill: parent

        CommonListView {
            id: treeView

            anchors.fill: parent

            delegate: TreeViewDelegate2{}
            model: gradingCriteriaModel
        }
        Scrollbar {
            target: treeView
        }
    }
}
