import QtQuick 2.0

Rectangle {
    id: decorativeRect

    property alias text: gradingCriteriaText.text
    property bool buttonsVisible
    property bool editable
    property bool expandable
    property bool expanded
    property var model

    signal expandClicked
    signal headerClicked

    width: parent.width
    height: gradingCriteriaText.height
    anchors.horizontalCenter: parent.horizontalCenter
    color: "transparent"

    MouseArea {
        anchors.fill: parent
        onClicked: headerClicked()
    }

    Row {
        id: rowContainer

        width: parent.width

        IconButton {
            id: openArrow

            anchors.verticalCenter: parent.verticalCenter
            icon: (expanded) ? "\uf0d7" : "\uf0da"
            opacity: { (expandable) ? 1 : 0 }

            onClicked: {
                expandClicked()
                addButton.state = "mouseOut"
                modifyButton.state = "mouseOut"
                deleteButton.state = "mouseOut"
            }
            enabled: { (expandable) ? 1: 0 }
        }

        Text {
            id: gradingCriteriaText
            width: calculateTextWidth()

            font.pointSize: 16
            wrapMode: Text.WordWrap
        }

        IconButton {
            id: addButton
            icon: "\uf067"
            hoverText: "Add Item"
            anchors.verticalCenter: parent.verticalCenter
            visible: buttonsVisible
            onClicked: {
                wizardContent.sourceComponent = addCriteriaItemDialog
                wizardContent.show()
            }
        }

        IconButton {
            id: modifyButton
            icon: "\uf040"
            hoverText: "Modify"
            anchors.verticalCenter: parent.verticalCenter
            visible: buttonsVisible
            onClicked: {
                wizardContent.sourceComponent = modifyGradingCriteriaDialog
                wizardContent.show()
            }
        }

        IconButton {
            id: deleteButton
            icon: "\uf014"
            hoverText: "Delete"
            anchors.verticalCenter: parent.verticalCenter
            visible: buttonsVisible
            onClicked: {
                wizardContent.sourceComponent = isDeleteGradingCriteriaOkDialog
                wizardContent.show()
            }
        }
    }

    function deleteGradingCriteria()
    {
        model.removeGradingCriteria(index)
    }

    function addNewCriteriaItem(text, level)
    {
        model.addCriteriaItem(index, text, level);
    }

    function modifyGradingCriteria(text)
    {
        model.modifyGradingCriteria(index, text);
    }

    // wizard component specifications
    Component {
        id: isDeleteGradingCriteriaOkDialog
        YesNoDialog {
            id: dialog
            dialogText: "Do you want to delete this item?\n\nIf you delete this item, all evaluations that use these\nelements will be converted to custom text items."

            Component.onCompleted:
            {
                dialog.onCanceled.connect(wizardContent.close)
                dialog.onNoClicked.connect(wizardContent.close)
                dialog.onYesClicked.connect(deleteGradingCriteria)
                dialog.onYesClicked.connect(wizardContent.close)
            }
        }
    }

    Component {
        id: addCriteriaItemDialog
        CriteriaItemEditDialog {
            id: dialog
            isModifyVisible: false
            explanationText: "Add grading criteria item.  Use the following tags to automatically insert text in Evaluations:\n" +
                             "  <Student_First_Name> = Student's first name\n" +
                             "  <Student_Middle_Name> = Student's middle name\n" +
                             "  <Student_Last_Name> = Student's last name\n" +
                             "  <Student_First_Last_Name> = Student's first and last name (e.g. John Smith)\n" +
                             "  <Student_he_she> = either \"he\" or \"she\" based on gender\n" +
                             "  <Student_his_her> = either \"his\" or \"her\" based on gender\n" +
                             "  <Student_him_her> = either \"him\" or \"her\" based on gender\n" +
                             "  <Student_himself_herself> = either \"himself\" or \"herself\" based on gender";

            Component.onCompleted: {
                dialog.onCanceled.connect(wizardContent.close)
                dialog.onCancelClicked.connect(wizardContent.close)
                dialog.onAddClicked.connect(addNewCriteriaItem)
                dialog.onAddClicked.connect(wizardContent.close)
            }
        }
    }

    Component {
        id: modifyGradingCriteriaDialog
        SingleLineTextEditDialog {
            id: dialog
            startingText: gradingCriteriaString
            explanationText: "Change the category name to:"

            Component.onCompleted: {
                dialog.onCanceled.connect(wizardContent.close)
                dialog.onCancelClicked.connect(wizardContent.close)
                dialog.onOkClicked.connect(modifyGradingCriteria)
                dialog.onOkClicked.connect(wizardContent.close)
            }
        }
    }

    function calculateTextWidth()
    {
        if(decorativeRect.editable === true)
        {
            return rowContainer.width - openArrow.width - addButton.width - modifyButton.width - deleteButton.width - (rowContainer.spacing*4)
        }
        else
        {
            return rowContainer.width - openArrow.width - (rowContainer.spacing)
        }
    }

}
