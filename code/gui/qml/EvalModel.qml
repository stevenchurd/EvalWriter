import QtQuick 2.0

Item {
    id: wrapper

    anchors.fill: parent
    anchors.margins: 5

    DropArea {
        anchors.fill: flowListView
        keys: ["add"]

        onDropped: {
            if(flowListView.findNearestItemIndex(drop.x, drop.y) !== -1)
            {
                flowListView.model.model.addCriteriaItem(flowListView.findNearestItemIndex(drop.x, drop.y), drop.source.itemUniqueId)
            }
        }
    }

    FlowListView {
        id: flowListView

        height: parent.height
        width: wrapper.width - (scrollbar.width + 5)

        displaced: Transition {
            NumberAnimation { properties: "x,y"; easing.type: Easing.OutQuad }
        }

        model: VisualDataModel {
            model: evalModel
            delegate: EvalItemDelegateFull{ }
        }
    }

    Scrollbar {
        id: scrollbar
        target: flowListView
    }
}
