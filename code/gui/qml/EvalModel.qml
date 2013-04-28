import QtQuick 2.0

Item {
    id: wrapper

    property string currentViewType: "largeDelegateView"
    property var evalModel

    anchors.fill: parent
    anchors.margins: 10

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
            color: (currentViewType == "textOnlyView") ? "#CCCCCC" : "transparent"
        }

        IconButton {
            id: smallDelegateViewButton
            anchors.right: textOnlyViewButton.left
            anchors.bottom: parent.bottom
            icon: "\uf066"
            hoverText: "Small Item View"
            onClicked: currentViewType = "smallDelegateView"
            color: (currentViewType == "smallDelegateView") ? "#CCCCCC" : "transparent"
        }

        IconButton {
            id: largeDelegateViewButton
            anchors.right: smallDelegateViewButton.left
            anchors.bottom: parent.bottom
            icon: "\uf065"
            hoverText: "Large Item View"
            onClicked: currentViewType = "largeDelegateView"
            color: (currentViewType == "largeDelegateView") ? "#CCCCCC" : "transparent"
        }

        IconButton {
            id: copyText
            anchors.right: largeDelegateViewButton.left
            anchors.bottom: parent.bottom
            icon: "\uf0c5"
            hoverText: "Copy Text"
            onClicked: {
                evTxt.selectAll()
                evTxt.copy()
                evTxt.deselect()
            }
            visible: currentViewType == "textOnlyView"
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

    Text {
        anchors.fill: flowListView
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter

        visible: flowListView.count == 0
        text: "Drop Items Here"
        color: "#DDDDDD"
        font.pointSize: 24
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
        contentHeight: evTxt.contentHeight

        clip: true

        anchors.top: headerItem.bottom
        anchors.margins: 5
        height: parent.height - headerItem.height
        width: wrapper.width - (scrollbar.width + 5)
        visible: (currentViewType === "textOnlyView")

        TextEdit {
            id: evTxt
            height: wrapper.height
            width: wrapper.width - (scrollbar.width + 5)
            anchors.margins: 5

            text: evalModel.getFullEvalText()
            wrapMode:TextEdit.WordWrap
            renderType: TextEdit.NativeRendering
            font.pointSize: 12
            readOnly: true
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
        visible: currentViewType !== "textOnlyView"
        anchors.left: scrollbar.right
        anchors.top: headerItem.bottom
        model: evalModel
        listOfItems: flowListView
    }

    Component.onCompleted: listOperationsContainer.fillListOperationsModel()
}
