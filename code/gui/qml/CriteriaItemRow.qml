import QtQuick 2.0

Rectangle {
    id: decorativeRect

    property alias text: criteriaText.text
    property int criteriaLevelIndicator
    property bool buttonsVisible
    property var model

    signal itemClicked(int index)

    height: criteriaText.height + 5
    color: "transparent"

    MouseArea {
        anchors.fill: parent
        onClicked: itemClicked(index)
    }

    Row {
        id: rowContainer

        width: parent.width
        spacing: 10

        Rectangle {
            id: indentRect
            width: 40
            height: parent.height
            color: "transparent"
        }

        Rectangle {
            id: levelIndicator
            width: 7
            height: parent.height
            anchors.verticalCenter: parent.verticalCenter

            border.color: "black"
            antialiasing: true
            color: getColor()

            function getColor()
            {
                switch(criteriaLevelIndicator)
                {
                    case 0:
                        return "green"
                    case 1:
                        return "lightgreen"
                    case 2:
                        return "yellow"
                    case 3:
                        return "#ff6666"
                    case 4:
                        return "red"
                    default:
                        break;
                }
            }
            radius: width*.5
        }

        Text {
            id: criteriaText
            width: {
                parent.width -
                        indentRect.width -
                        levelIndicator.width -
                        modifyButton.width -
                        deleteButton.width -
                        (rowContainer.spacing*4)
            }

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
        CriteriaItemDialog {
            id: dialog
            explanationText: "Modifying existing items will change them in all evaluations\ninwhich they are used.  If you do not with to do this\nyou may add this as a new item."
            startingText: text

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
