import QtQuick 2.0
import "utilities.js" as JsUtil

MouseArea {
    id: delegateRoot

    property int visualIndex: VisualDataModel.itemsIndex
    property string currentViewType

    Component.onCompleted: width = calculateDelegateWidth()
    height: {
        if(currentViewType === "largeDelegateView")
        {
            if(evalItemSelected)
                return fitHeight()
            else
                return 80
        }
        else if(currentViewType === "smallDelegateView")
        {
            return topRow.height
        }
    }
    drag.target: itemRect

    onCanceled: itemRect.Drag.cancel()
    onClicked: toggleItemSelection()

    Behavior on height {
        NumberAnimation { duration: 100 }
    }

    Behavior on width {
        NumberAnimation { duration: 100 }
    }

    Rectangle {
        id: itemRect
        height: delegateRoot.height
        width: delegateRoot.width
        clip: true
        anchors {
            horizontalCenter: parent.horizontalCenter;
            verticalCenter: parent.verticalCenter
        }
        color: (evalItemSelected) ? "#BBBBBB" : "#EEEEEE"
        border.color: "#EEEEEE"

        Drag.onActiveChanged: if(!evalItemSelected) { toggleItemSelection() }

        Drag.active: delegateRoot.drag.active
        Drag.source: delegateRoot
        Drag.hotSpot.x: width/2
        Drag.hotSpot.y: height/2
        Drag.keys: ["move"]

        Rectangle {
            id: colorIndicator
            anchors.verticalCenter: parent.verticalCenter
            height: parent.height-(parent.border.width*2)
            width: 5
            color: JsUtil.getEvalItemColor(evalItemLevel)
        }

        Item {
            id: topRow
            height: removeButton.height
            width: parent.width-colorIndicator.width
            anchors.left: colorIndicator.right
            anchors.leftMargin: 5

            Text {
                id: titleTextArea
                anchors.verticalCenter: parent.verticalCenter
                clip: true

                text: evalItemTitle
                width: parent.width - buttonsWidth()
                font.bold: true
                renderType: Text.NativeRendering
            }

            IconButton {
                id: editButton
                anchors.right: removeButton.left
                icon: "\uf040"
                hoverText: "Edit"
                visible: evalItemIsEditable && evalItemSelected
                onClicked: {
                    wizardContent.sourceComponent = editCustomTextItemDialog
                    wizardContent.show()
                }
            }

            IconButton {
                id: removeButton
                anchors.right: topRow.right
                anchors.rightMargin: 5
                icon: "\uf014"
                hoverText: "Remove"
                visible: evalItemSelected
                onClicked: {
                    wizardContent.sourceComponent = isRemoveEvalItemOkDialog
                    wizardContent.show()
                }
            }
        }

        Text {
            id: bottomRow
            height: parent.height - topRow.height - 8
            width: parent.width - colorIndicator.width - 10
            anchors.left: colorIndicator.right
            anchors.top: topRow.bottom
            anchors.leftMargin: 5
            anchors.topMargin: 5

            text: evalItemString
            renderType: Text.NativeRendering
            wrapMode: Text.WordWrap
        }

        states: [
            State {
                when: itemRect.Drag.active
                ParentChange {
                    target: itemRect
                    parent: screenContainer
                }

                AnchorChanges {
                    target: itemRect;
                    anchors.horizontalCenter: undefined;
                    anchors.verticalCenter: undefined
                }
            }
        ]
    }

    DropArea {
        anchors.fill: delegateRoot

        keys: ["move", "add"]

        onEntered: {
            if(drag.keys[0] === "move")
            {
                delegateRoot.VisualDataModel.model.model.moveEvalItem(drag.source.visualIndex, delegateRoot.visualIndex)
            }
        }
        onDropped: {
            if(drop.keys[0] === "add")
            {
                delegateRoot.VisualDataModel.model.model.addCriteriaItem(index, drop.source.itemUniqueId)
            }
        }
    }

    function buttonsWidth()
    {
        return ((evalItemIsEditable) ? editButton.width : 0) + removeButton.width
    }

    function calculateDelegateWidth()
    {
        // absolute max width is 250
        // height is always 80
        var titleWidth = titleTextArea.paintedWidth + buttonsWidth() + colorIndicator.width + 5
        var textWidth = bottomRow.paintedWidth + colorIndicator.width + 5

        var fittedWidth = Math.max(titleWidth, textWidth)
        fittedWidth = Math.min(fittedWidth, 250)

        return fittedWidth
    }

    function fitHeight()
    {
        if(bottomRow.paintedHeight > bottomRow.height)
        {
            return bottomRow.paintedHeight+topRow.height + 8
        }

        return delegateRoot.height
    }

    function toggleItemSelection()
    {
        if(evalItemSelected)
        {
            delegateRoot.VisualDataModel.model.model.deselectItem(index)
        }
        else
        {
            delegateRoot.VisualDataModel.model.model.deselectAllItems()
            delegateRoot.VisualDataModel.model.model.selectItem(index)
        }
    }

    function removeEvalItem()
    {
        delegateRoot.VisualDataModel.model.model.removeItem(index)
    }

    function editCustomTextItem(newTitle, newString)
    {
        delegateRoot.VisualDataModel.model.model.editItemString(index, newTitle, newString);
        delegateRoot.width = calculateDelegateWidth()
    }

    // wizard component definitions
    Component {
        id: isRemoveEvalItemOkDialog
        YesNoDialog {
            id: dialog
            dialogText: "Do you want to remove this item from the Evaluation?"

            Component.onCompleted:
            {
                dialog.onCanceled.connect(wizardContent.close)
                dialog.onNoClicked.connect(wizardContent.close)
                dialog.onYesClicked.connect(removeEvalItem)
                dialog.onYesClicked.connect(wizardContent.close)
            }
        }
    }

    Component {
        id: editCustomTextItemDialog
        CustomTextItemEditDialog {
            id: dialog
            dialogText: "Edit the custom text item:"
            startingText: evalItemString
            startingTitle: evalItemTitle
            acceptButtonText: "Edit"

            Component.onCompleted:
            {
                dialog.onCanceled.connect(wizardContent.close)
                dialog.onCancelClicked.connect(wizardContent.close)
                dialog.onAcceptedClicked.connect(editCustomTextItem)
                dialog.onAcceptedClicked.connect(wizardContent.close)
            }
        }
    }

}



