import QtQuick 2.0
import "utilities.js" as JsUtil
import "criteriaItemRowCreation.js" as CriteriaItemRowCreator

Rectangle {
    id: decorativeRect

    property alias text: criteriaText.text
    property int criteriaLevelValue
    property bool editable: false
    property bool buttonsVisible: false
    property bool isSelected: true
    property var model

    // this is only used when creating dummy rows for dragging that
    // look just like the original item but don't have the underlying
    // model connection
    property var itemUniqueId: uniqueId

    signal itemClicked(int index)

    height: criteriaText.height
    color: (isSelected) ? "lightsteelblue" : "transparent"
    border.color: "lightgray"
    clip: true
    smooth: true

    MouseArea {
        anchors.fill: parent

        onClicked: itemClicked(index)
        onPressed: {
            itemClicked(index)
            if(!editable)
            {
                gradingCriteriaList.interactive = false
                CriteriaItemRowCreator.startDrag(mouse, decorativeRect)
            }
        }
        onPositionChanged: {
            if(!editable)
            {
                CriteriaItemRowCreator.continueDrag(mouse)
            }
        }
        onCanceled: {
            if(!editable)
            {
                CriteriaItemRowCreator.cancelDrag()
                gradingCriteriaList.interactive = true
            }
        }
        onReleased: {
            if(!editable)
            {
                CriteriaItemRowCreator.endDrag(mouse)
                gradingCriteriaList.interactive = true
            }
        }
    }

    Row {
        id: rowContainer

        width: parent.width
        spacing: 10

        Rectangle {
            id: levelIndicator
            width: 7
            height: rowContainer.height
            anchors.verticalCenter: rowContainer.verticalCenter

            border.color: "black"
            antialiasing: true
            color: JsUtil.getEvalItemColor(criteriaLevelValue)
        }

        Text {
            id: criteriaText
            width: calculateTextWidth()

            font.pointSize: 10
            wrapMode: Text.WordWrap
            renderType: Text.NativeRendering
        }

        TextButton{
            id: modifyButton
            text: "Modify"
            anchors.top: parent.top
            visible: buttonsVisible
            onClicked: {
                wizardContent.sourceComponent = modifyCriteriaItemDialog
                wizardContent.show()
            }
        }

        TextButton{
            id: deleteButton
            text: "Delete"
            anchors.top: parent.top
            visible: buttonsVisible
            onClicked: {
                wizardContent.sourceComponent = isDeleteCriteriaItemOkDialog
                wizardContent.show()
            }
        }
    }

    function calculateTextWidth()
    {
        if(decorativeRect.editable === true)
        {
            return rowContainer.width -
                    levelIndicator.width -
                    modifyButton.width -
                    deleteButton.width -
                    (rowContainer.spacing*4)
        }
        else
        {
            return rowContainer.width - levelIndicator.width - (rowContainer.spacing*2)
        }
    }

    function deleteCriteriaItem()
    {
        model.removeCriteriaItem(index)
    }

    function modifyCriteriaItem(newText, level)
    {
        model.modifyCriteriaItem(index, newText, level)
    }

    function sendAddCriteriaItem(text, level)
    {
        model.addCriteriaItem(text, level)
    }

    // component definitions
    Component {
        id: isDeleteCriteriaItemOkDialog
        YesNoDialog {
            id: dialog
            dialogText: "Do you want to delete this item?\n\nIf you delete this item, any evaluations that use this item\nwill be converted to a custom text item."

            Component.onCompleted: {
                dialog.onCanceled.connect(wizardContent.close)
                dialog.onNoClicked.connect(wizardContent.close)
                dialog.onYesClicked.connect(deleteCriteriaItem)
                dialog.onYesClicked.connect(wizardContent.close)
            }
        }
    }

    Component {
        id: modifyCriteriaItemDialog
        CriteriaItemEditDialog {
            id: dialog
            explanationText: "Modifying existing items will change them in all evaluations\ninwhich they are used.  If you do not with to do this\nyou may add this as a new item."
            startingText: text
            currentLevel: criteriaLevelValue

            Component.onCompleted: {
                dialog.onCanceled.connect(wizardContent.close)
                dialog.onModifyClicked.connect(wizardContent.close)
                dialog.onModifyClicked.connect(modifyCriteriaItem)
                dialog.onCancelClicked.connect(wizardContent.close)
                dialog.onAddClicked.connect(sendAddCriteriaItem)
                dialog.onAddClicked.connect(wizardContent.close)
            }
        }
    }
}
