import QtQuick 2.0
import "utilities.js" as JsUtil
import CppEnums 1.0

Rectangle {
    id: wrapper
    height: parent.height
    width: 150
    color: "transparent"

    property var mostRecentOperation
    property var mostRecentItemChooserList
    property var model
    property ListView listOfItems

    ListModel {
        id: operationsModel
    }

    ListView {
        id: operationsListView
        anchors.fill: parent
        anchors.margins: 5
        spacing: 5
        interactive: false

        model: operationsModel
        delegate: TextButton {
            visible: (JsUtil.isOperationIndexDependent(operation) && listOfItems.currentIndex < 0) ? false : true
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
                return addStudentDialog

            case QStudentsListModel.AddExistingStudentToCourse:
                return itemChooserDialog

            case QStudentsListModel.RenameStudent:
                return renameStudentDialog

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

            //
            // Grading Criteria operations
            //
            case QGradingCriteriaModel.AddGradingCriteria:
                return addItemDialog

            default:
                console.log("No component defined: " + operation)
        }
    }


    function addStudent(firstName, middleName, lastName)
    {
        wrapper.model.addStudent(firstName, middleName, lastName)
    }


    function renameStudent(firstName, middleName, lastName)
    {
        wrapper.model.renameStudent(firstName, middleName,
                                    lastName, listOfItems.currentIndex)
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

    // dialog components
    Component {
        id: addStudentDialog
        AddStudentDialog {
            id: dialog
            explanationText: wrapper.model.getOperationExplanationText(mostRecentOperation, listOfItems.currentIndex)

            Component.onCompleted: {
                dialog.onCanceled.connect(wizardContent.close)
                dialog.onCancelClicked.connect(wizardContent.close)
                dialog.onOkClicked.connect(addStudent)
                dialog.onOkClicked.connect(wizardContent.close)
            }
        }

    }


    Component {
        id: renameStudentDialog
        AddStudentDialog {
            id: dialog
            explanationText: wrapper.model.getOperationExplanationText(mostRecentOperation, listOfItems.currentIndex)

            Component.onCompleted: {
                dialog.onCanceled.connect(wizardContent.close)
                dialog.onCancelClicked.connect(wizardContent.close)
                dialog.onOkClicked.connect(renameStudent)
                dialog.onOkClicked.connect(wizardContent.close)
            }

        }
    }


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
