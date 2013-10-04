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

    height: criteriaText.height + 5
    color: (isSelected) ? "#EEEEEE" : "transparent"
    clip: true

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
        height: parent.height
        spacing: 5

        Rectangle {
            id: levelIndicator
            width: 3
            height: rowContainer.height
            anchors.verticalCenter: rowContainer.verticalCenter
            color: JsUtil.getEvalItemColor(criteriaLevelValue)
        }

        Text {
            id: criteriaText
            width: calculateTextWidth()
            anchors.verticalCenter: parent.verticalCenter

            font.pointSize: 10
            wrapMode: Text.WordWrap
            renderType: Text.NativeRendering
        }

        IconButton{
            id: modifyButton
            icon: "\uf040"
            hoverText: "Modify"
            size: 12
            anchors.top: parent.top
            visible: buttonsVisible
            onClicked: {
                dialogContent.setSourceComponentWithSecondarySubmit("CriteriaItemEditDialog.qml",
                                                                   {"explanationText": "Modifying existing items will change them in all evaluations\ninwhich they are used.  If you do not with to do this\nyou may add this as a new item.",
                                                                    "startingText": text,
                                                                    "headerText":  "modify grading criteria item",
                                                                    "currentLevel": criteriaLevelValue},
                                                                    sendAddCriteriaItem,
                                                                    modifyCriteriaItem)
                dialogContent.show()
            }
        }

        IconButton{
            id: deleteButton
            icon: "\uf014"
            hoverText: "Delete"
            size: 12
            anchors.top: parent.top
            visible: buttonsVisible
            onClicked: {
                dialogContent.setSourceComponentWithSubmit("YesNoDialog.qml",
                                                          {"dialogText": "Do you want to delete this item?\n\nIf you delete this item, any evaluations that use this item\nwill be converted to a custom text item.",
                                                           "headerText": "delete grading criteria"},
                                                           deleteCriteriaItem)
                dialogContent.show()
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
}
