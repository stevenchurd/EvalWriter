import QtQuick 2.0
import "utilities.js" as JsUtil

MouseArea {
    id: delegateRoot

    property int visualIndex: VisualDataModel.itemsIndex

    width: stringWidth(evalItemString)
    height: 80 /* TODO: making item bigger to fit text can be done here */
    drag.target: icon

    onClicked: toggleItemSelection()

    Rectangle {
        id: icon
        width: stringWidth(evalItemString)
        height: delegateRoot.height
        clip: true
        anchors {
            horizontalCenter: parent.horizontalCenter;
            verticalCenter: parent.verticalCenter
        }
        color: (evalItemSelected) ? "lightsteelblue" : "white"
        border.color: "black"
        radius: 3

        Drag.onActiveChanged: if(!evalItemSelected) { toggleItemSelection() }

        Drag.active: delegateRoot.drag.active
        Drag.source: delegateRoot
        Drag.hotSpot.x: width/2
        Drag.hotSpot.y: height/2
        Drag.keys: ["move"]

        Item {
            id: topRow
            height: removeButton.height
            width: parent.width

            Text {
                text: evalItemTitle
                font.bold: true
                renderType: Text.NativeRendering
            }

            TextButton {
                id: editButton
                anchors.right: removeButton.left
                text: "Edit"
                visible: evalItemIsEditable && evalItemSelected
                onClicked: {
                    wizardContent.sourceComponent = editCustomTextItemDialog
                    wizardContent.show()
                }
            }

            TextButton {
                id: removeButton
                anchors.right: topRow.right
                text: "X"
                visible: evalItemSelected
                onClicked: {
                    wizardContent.sourceComponent = isRemoveEvalItemOkDialog
                    wizardContent.show()
                }
            }
        }

        Row {
            id: bottomRow
            height: parent.height - topRow.height
            width: parent.width
            anchors.top: topRow.bottom

            Rectangle {
                id: colorIndicator
                height: parent.height
                width: 5
                border.color: "black"
                color: JsUtil.getEvalItemColor(evalItemLevel)
            }

            Text {
                height: parent.height
                width: parent.width-colorIndicator.width
                text: evalItemString
                renderType: Text.NativeRendering
                wrapMode: Text.WordWrap
            }
        }

        states: [
            State {
                when: icon.Drag.active
                ParentChange {
                    target: icon
                    parent: flowListView
                }

                AnchorChanges {
                    target: icon;
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
                delegateRoot.VisualDataModel.model.model.move(drag.source.visualIndex, delegateRoot.visualIndex)
            }
        }
        onDropped: {
            if(drop.keys[0] === "add")
            {
                delegateRoot.VisualDataModel.model.model.addCriteriaItem(index, drop.source.itemUniqueId)
            }
        }
    }

    function stringWidth(s)
    {
        return Math.min(String(s).length * 5, 250);
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

            Component.onCompleted:
            {
                dialog.onCanceled.connect(wizardContent.close)
                dialog.onCancelClicked.connect(wizardContent.close)
                dialog.onEditClicked.connect(editCustomTextItem)
                dialog.onEditClicked.connect(wizardContent.close)
            }
        }
    }

}


