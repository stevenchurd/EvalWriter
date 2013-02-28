import QtQuick 2.0

Item {
    id: wrapper

    anchors.fill: parent

    FlowListView {
        id: root
        anchors.fill: parent

        displaced: Transition {
            NumberAnimation { properties: "x,y"; easing.type: Easing.OutQuad }
        }

        model: VisualDataModel {
            model: evalModel
            delegate: EvalItemDelegate{ }
        }
    }
}
