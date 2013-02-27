import QtQuick 2.0

Item {
    id: wrapper

    anchors.fill: parent

    GridView {
        id: root
        anchors.fill: parent
        cellHeight: 70
        cellWidth: 125

        displaced: Transition {
            NumberAnimation { properties: "x,y"; easing.type: Easing.OutQuad }
        }

        model: VisualDataModel {
            model: evalModel
            delegate: EvalItemDelegate{}
        }
    }
}
