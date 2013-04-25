import QtQuick 2.0

Item {
    id: wrapper

    property string currentViewType: "largeDelegateView"
    property var evalModel

    anchors.fill: parent
    anchors.margins: 5

    Rectangle {
        id: headerItem

        height: textOnlyViewButton.height
        width: parent.width

        border.color: "lightgray"

        Checkbox {
            id: checkbox
            width: parent.height - 5
            height: parent.height - 5
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: parent.left
            anchors.leftMargin: 5

            initiallyChecked: evalModel.isEvalComplete()
            onCheckToggled: evalModel.toggleEvalComplete()
        }

        Text {
            anchors.left: checkbox.right
            anchors.leftMargin: 5
            anchors.verticalCenter: parent.verticalCenter
            text: "Complete"
            renderType: Text.NativeRendering
        }

        IconButton {
            id: textOnlyViewButton
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            icon: "\uf031"
            hoverText: "Text Only View"
            onClicked: currentViewType = "textOnlyView"
        }

        IconButton {
            id: smallDelegateViewButton
            anchors.right: textOnlyViewButton.left
            anchors.bottom: parent.bottom
            icon: "\uf066"
            hoverText: "Small Item View"
            onClicked: currentViewType = "smallDelegateView"
        }

        IconButton {
            id: largeDelegateViewButton
            anchors.right: smallDelegateViewButton.left
            anchors.bottom: parent.bottom
            icon: "\uf065"
            hoverText: "Large Item View"
            onClicked: currentViewType = "largeDelegateView"
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
        anchors.margins: 5
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
        anchors.top: headerItem.bottom
        model: evalModel
        listOfItems: flowListView
    }

    Component.onCompleted: listOperationsContainer.fillListOperationsModel()
}
