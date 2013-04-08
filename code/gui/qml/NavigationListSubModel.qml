import QtQuick 2.0
import "pageCreator.js" as PageCreator
import "utilities.js" as JsUtil
import CppEnums 1.0

Rectangle {
    id: wrapper
    anchors.fill: parent
    property var model
    property var modelType
    property ListModel modelOperations
    property var mostRecentItemChooserList
    property var mostRecentOperation

    clip: true

    ListView {
        id: listOfItems
        height: parent.height
        width: parent.width - listOperationsContainer.width - (scrollbar.width + 5)
        model: wrapper.model

        highlight: Rectangle {
            width: (listOfItems.width > 400) ? 400 : listOfItems.width
            color: "lightsteelblue"
        }

        delegate: MouseArea {
            id: delegateWrapper
            height: 60
            // TODO: work on resizing objects eventually
            width: listOfItems.width > 400 ? 400 : listOfItems.width - (scrollbar.width + 5)

            readonly property string itemString: displayString

            Text {
                anchors.verticalCenter: parent.verticalCenter
                renderType: Text.NativeRendering
                text: displayString
            }

            Rectangle {
                height:20
                width: 20
                anchors.right: parent.right
                anchors.margins: 10
                anchors.verticalCenter: parent.verticalCenter
                color: "green"
                MouseArea {
                    anchors.fill: parent

                    onClicked: {
                        pageStack.push(PageCreator.createModelByType(wrapper.modelType,
                                                                     wrapper.model.getSubModelFromIndex(index)))
                    }
                }
            }
            onClicked: delegateWrapper.ListView.view.currentIndex = index
        }
    }

    Scrollbar {
        id: scrollbar
        target: listOfItems
    }

    Rectangle {
        id: listOperationsContainer
        height: parent.height
        width: 150
        anchors.left: scrollbar.right
        color: "red"

        ListModel {
            id: operationsModel
        }

        ListView {
            anchors.fill: parent
            anchors.margins: 5
            spacing: 5
            interactive: false

            model: operationsModel
            delegate: TextButton {
                width: parent.width

                text: operationText
                onClicked: {
                    mostRecentOperation = operation
                    if(componentToDisplay === itemChooserDialog)
                    {
                        mostRecentItemChooserList = wrapper.model.getOptionListForOperation(operation)
                    }
                    wizardContent.sourceComponent = componentToDisplay
                    wizardContent.show()
                }
            }
        }
    }

    Component.onCompleted: {
        fillListOperationsModel()
    }


    function fillListOperationsModel()
    {
        var supportedOperations = wrapper.model.getSubModelOperations()
        operationsModel.clear()

        for(var i = 0; i < supportedOperations.length; i++)
        {
            operationsModel.append({"operationText": JsUtil.getOperationString(supportedOperations[i]),
                                    "componentToDisplay": getOperationComponent(supportedOperations[i]),
                                    "operation": supportedOperations[i]})
        }
    }

    function addItem(newName)
    {
        wrapper.model.addItem(newName)
    }


    function removeItem()
    {
        wrapper.model.removeItem(listOfItems.currentIndex)
    }


    function renameItem(newName)
    {
        wrapper.model.renameItem(newName, listOfItems.currentIndex)
    }


    function chooseItem(row)
    {
        wrapper.model.optionListSelection(mostRecentOperation, row);
    }


    function getOperationComponent(operation)
    {
        switch(operation) {
            //
            // Course operations
            //
            case QCoursesListModel.AddCourse:
                return addItemDialog

            case QCoursesListModel.RemoveCourse:
                return removeItemDialog

            case QCoursesListModel.RenameCourse:
                return renameItemDialog

            case QCoursesListModel.RemoveExistingCourseFromStudent:
                return removeItemDialog

            case QCoursesListModel.AddExistingCourseToStudent:
                return itemChooserDialog

            //
            // Eval Set operations
            //
            case QEvalSetsListModel.AddEvalSet:
                return addItemDialog

            case QEvalSetsListModel.RemoveEvalSet:
                return removeItemDialog

            case QEvalSetsListModel.RenameEvalSet:
                return renameItemDialog

            //
            // Student operations
            //
            case QStudentsListModel.AddStudent:
                // TODO
                //return addStudentDialog

            case QStudentsListModel.AddExistingStudentToCourse:
                return itemChooserDialog

            case QStudentsListModel.RemoveStudent:
                return removeItemDialog

            case QStudentsListModel.RemoveStudentFromCourse:
                return removeItemDialog

            //
            // Eval operations
            //
            case QEvalsListModel.AddEval:
                return addItemDialog

            case QEvalsListModel.RemoveEval:
                return removeItemDialog

            case QEvalsListModel.RenameEval:
                return renameItemDialog

            case QEvalsListModel.AddExistingEvalToEvalSet:
                return itemChooserDialog

            case QEvalsListModel.RemoveEvalFromEvalSet:
                return removeItemDialog

            default:
                console.log("No component defined: " + operation)
        }
    }


    // dialog componenets
    Component {
        id: addItemDialog
        SingleLineTextEditDialog {
            id: dialog
            explanationText: wrapper.model.getOperationExplanationText(mostRecentOperation, listOfItems.currentIndex)

            Component.onCompleted: {
                dialog.onCanceled.connect(wizardContent.close)
                dialog.onCancelClicked.connect(wizardContent.close)
                dialog.onOkClicked.connect(addItem)
                dialog.onOkClicked.connect(wizardContent.close)
            }
        }
    }


    Component {
        id: removeItemDialog
        YesNoDialog {
            id: dialog
            dialogText: wrapper.model.getOperationExplanationText(mostRecentOperation, listOfItems.currentIndex)

            Component.onCompleted: {
                dialog.onCanceled.connect(wizardContent.close)
                dialog.onNoClicked.connect(wizardContent.close)
                dialog.onYesClicked.connect(removeItem)
                dialog.onYesClicked.connect(wizardContent.close)
            }
        }
    }


    Component {
        id: renameItemDialog
        SingleLineTextEditDialog {
            id: dialog
            explanationText: wrapper.model.getOperationExplanationText(mostRecentOperation, listOfItems.currentIndex)
            startingText: listOfItems.currentItem.itemString

            Component.onCompleted: {
                dialog.onCanceled.connect(wizardContent.close)
                dialog.onCancelClicked.connect(wizardContent.close)
                dialog.onOkClicked.connect(renameItem)
                dialog.onOkClicked.connect(wizardContent.close)
            }
        }
    }

    Component {
        id: itemChooserDialog
        ListChooserDialog {
            id: dialog
            explanationText: wrapper.model.getOperationExplanationText(mostRecentOperation, listOfItems.currentIndex)
            stringList: mostRecentItemChooserList

            Component.onCompleted: {
                dialog.onCanceled.connect(wizardContent.close)
                dialog.onCancelClicked.connect(wizardContent.close)
                dialog.onOkClicked.connect(chooseItem)
                dialog.onOkClicked.connect(wizardContent.close)
            }
        }
    }
}
