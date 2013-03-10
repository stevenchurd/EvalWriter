import QtQuick 2.0

Item {
    id: wrapper

    anchors.fill: parent
    anchors.margins: 5

    Item {
        height: childrenRect.height
        width: parent.width
        id: headerItem
        Text {
            text: evalModel.getEvalTitle()
            font.pointSize: 20
            smooth: true
            wrapMode: Text.WordWrap
            width: wrapper.width
            renderType: Text.NativeRendering
        }
    }

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

        anchors.top: headerItem.bottom
        height: parent.height - headerItem.height
        width: wrapper.width - (scrollbar.width + 5)
        clip: true

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
