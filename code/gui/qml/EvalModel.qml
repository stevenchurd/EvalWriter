import QtQuick 2.0

Item {
    id: wrapper

    anchors.fill: parent

    DropArea {
        anchors.fill: parent
        keys: ["add"]

        onDropped: {
            root.model.model.addCriteriaItem(root.findNearestItemIndex(drop.x, drop.y), drop.source.itemUniqueId)
        }
    }

    FlowListView {
        id: root
        anchors.fill: parent

        displaced: Transition {
            NumberAnimation { properties: "x,y"; easing.type: Easing.OutQuad }
        }

        model: VisualDataModel {
            id: visualDataModel
            model: evalModel
            delegate: EvalItemDelegate{ }
        }
    }
}
