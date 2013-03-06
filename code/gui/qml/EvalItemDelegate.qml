import QtQuick 2.0
import "utilities.js" as JsUtil

MouseArea {
    id: delegateRoot

    property int visualIndex: VisualDataModel.itemsIndex

    width: stringWidth(evalItemString)
    height: 80
    drag.target: icon

    onClicked: toggleItemSelection()

    Rectangle {
        id: icon
        width: stringWidth(evalItemString)
        height: 75
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
        Drag.hotSpot.x: 36
        Drag.hotSpot.y: 36

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
                    parent: root
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
        anchors { fill: parent; margins: 15 }

        onEntered: {
            console.log("entered eval drop area")
            delegateRoot.VisualDataModel.model.model.move(drag.source.visualIndex, delegateRoot.visualIndex)
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

    function editCustomTextItem(newString)
    {
        delegateRoot.VisualDataModel.model.model.editItemString(index, newString);
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



