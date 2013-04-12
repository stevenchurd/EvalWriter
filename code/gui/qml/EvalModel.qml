import QtQuick 2.0

Item {
    id: wrapper

    property string currentViewType: "largeDelegateView"
    property var evalModel

    anchors.fill: parent
    anchors.margins: 5

    Item {
        height: evalTitle.height
        width: parent.width
        id: headerItem

        TextButton {
            id: textOnlyViewButton
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            text: "T"
            onClicked: currentViewType = "textOnlyView"
        }

        TextButton {
            id: smallDelegateViewButton
            anchors.right: textOnlyViewButton.left
            anchors.bottom: parent.bottom
            text: "s"
            onClicked: currentViewType = "smallDelegateView"
        }

        TextButton {
            id: largeDelegateViewButton
            anchors.right: smallDelegateViewButton.left
            anchors.bottom: parent.bottom
            text: "L"
            onClicked: currentViewType = "largeDelegateView"
        }

        Text {
            id: evalTitle
            text: evalModel.getEvalTitle()
            font.pointSize: 20
            wrapMode: Text.WordWrap
            width: wrapper.width-
                   (textOnlyViewButton.width +
                    smallDelegateViewButton.width +
                    largeDelegateViewButton.width)
            renderType: Text.NativeRendering
        }

    }

    DropArea {
        anchors.fill: flowListView
        visible: (currentViewType === "smallDelegateView" ||
                  currentViewType === "largeDelegateView")
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
        width: wrapper.width - (scrollbar.width + 5) - listOperationsContainer.width
        clip: true
        visible: (currentViewType === "smallDelegateView" ||
                  currentViewType === "largeDelegateView")

        displaced: Transition {
            NumberAnimation { properties: "x,y"; easing.type: Easing.OutQuad }
        }

        model: VisualDataModel {
            model: evalModel
            delegate: EvalItemDelegate{ currentViewType: wrapper.currentViewType}
        }
    }

    Flickable {
        id: evalTextView

        contentWidth: width;
        contentHeight: childrenRect.height

        clip: true

        anchors.top: headerItem.bottom
        anchors.margins: 20
        height: parent.height - headerItem.height
        width: wrapper.width - (scrollbar.width + 5)
        visible: (currentViewType === "textOnlyView")

        Text {
            id: evTxt
            width: wrapper.width - (scrollbar.width + 5)

            text: evalModel.getFullEvalText()
            wrapMode:Text.WordWrap
            renderType: Text.NativeRendering
            font.pointSize: 12
        }

        function updateEvalText() { evTxt.text = evalModel.getFullEvalText() }
    }

    onCurrentViewTypeChanged: evalTextView.updateEvalText()

    Scrollbar {
        id: scrollbar
        target: (currentViewType === "smallDelegateView" ||
                 currentViewType === "largeDelegateView") ?  flowListView : evalTextView
    }

    PageOperationsContainer {
        id: listOperationsContainer
        enabled: currentViewType !== "textOnlyView"
        anchors.left: scrollbar.right
        model: evalModel
        listOfItems: flowListView
    }

    Component.onCompleted: listOperationsContainer.fillListOperationsModel()
}
