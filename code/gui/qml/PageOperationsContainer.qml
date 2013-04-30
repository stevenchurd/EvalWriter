import QtQuick 2.0
import CppEnums 1.0

Rectangle {
    id: wrapper
    height: parent.height
    width: 150
    color: "transparent"

    property var mostRecentOperation
    property var mostRecentItemChooserList
    property var model
    property var listOfItems

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
            visible: (isOperationIndexDependent(operation) && listOfItems.currentIndex < 0) ? false : true
            width: parent.width

            text: operationText
            onClicked: {
                mostRecentOperation = operation
                if(componentToDisplay === itemChooserDialog ||
                   componentToDisplay === createEvalSetFromCourseDialog ||
                   componentToDisplay === createEvalSetFromEvalSetDialog)
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
            operationsModel.append({"operationText": getOperationString(supportedOperations[i]),
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
            case QEvalSetsListModel.CreateEvalSetFromCourse:
                return createEvalSetFromCourseDialog

            case QEvalSetsListModel.CreateEvalSetFromEvalSet:
                return createEvalSetFromEvalSetDialog

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

            //
            // Evaluation operations
            //
            case QEvaluationModel.AddCustomTextItem:
                return addCustomTextDialog

            default:
                console.log("No component defined: " + operation)
        }
    }

    function getOperationString(operation)
    {
        switch(operation) {
            // Course List operations
            case QCoursesListModel.AddCourse:
                return "Add New Class"

            case QCoursesListModel.RemoveCourse:
                return "Delete Class"

            case QCoursesListModel.RenameCourse:
                return "Rename Class"

            case QCoursesListModel.RemoveExistingCourseFromStudent:
                return "Remove Student from Class"

            case QCoursesListModel.AddExistingCourseToStudent:
                return "Add Student to Class"


            // Eval Set List Operations
            case QEvalSetsListModel.CreateEvalSetFromCourse:
                return "Create from Course"

            case QEvalSetsListModel.CreateEvalSetFromEvalSet:
                return "Create from Evaluation Set"

            case QEvalSetsListModel.AddEvalSet:
                return "Add Evaluation Set"

            case QEvalSetsListModel.RemoveEvalSet:
                return "Remove Evaluation Set"

            case QEvalSetsListModel.RenameEvalSet:
                return "Rename Evaluation Set"


            // Student List Operations
            case QStudentsListModel.AddStudent:
                return "Add Student"

            case QStudentsListModel.RemoveStudent:
                return "Remove Student"

            case QStudentsListModel.RenameStudent:
                return "Rename Student"

            case QStudentsListModel.AddExistingStudentToCourse:
                return "Add Existing Student"

            case QStudentsListModel.RemoveStudentFromCourse:
                return "Remove Student from Class"


            // Eval List Operations
            case QEvalsListModel.AddEval:
                return "Add Evaluation"

            case QEvalsListModel.RemoveEval:
                return "Remove Evalutation"

            case QEvalsListModel.RenameEval:
                return "Rename Evaluation"

            case QEvalsListModel.AddExistingEvalToEvalSet:
                return "Add Existing Evaluation"

            case QEvalsListModel.RemoveEvalFromEvalSet:
                return "Remove Evaluation from Set"


            // Grading Category Operations
            case QGradingCriteriaModel.AddGradingCriteria:
                return "Add Grading Category"


            // Evaluation operations
            case QEvaluationModel.AddCustomTextItem:
                return "Add Custom Text"


            default:
                console.log("Error: operation not defined: " + operation)
                return String(operation)
        }
    }


    function isOperationIndexDependent(operation)
    {
        switch(operation) {
            // Course List operations
            case QCoursesListModel.AddCourse:
                return false

            case QCoursesListModel.RemoveCourse:
                return true

            case QCoursesListModel.RenameCourse:
                return true

            case QCoursesListModel.RemoveExistingCourseFromStudent:
                return true

            case QCoursesListModel.AddExistingCourseToStudent:
                return false


            // Eval Set List Operations
            case QEvalSetsListModel.CreateEvalSetFromCourse:
                return false

            case QEvalSetsListModel.CreateEvalSetFromEvalSet:
                return false

            case QEvalSetsListModel.AddEvalSet:
                return false

            case QEvalSetsListModel.RemoveEvalSet:
                return true

            case QEvalSetsListModel.RenameEvalSet:
                return true


            // Student List Operations
            case QStudentsListModel.AddStudent:
                return false

            case QStudentsListModel.RemoveStudent:
                return true

            case QStudentsListModel.RenameStudent:
                return true

            case QStudentsListModel.AddExistingStudentToCourse:
                return false

            case QStudentsListModel.RemoveStudentFromCourse:
                return true


            // Eval List Operations
            case QEvalsListModel.AddEval:
                return false

            case QEvalsListModel.RemoveEval:
                return true

            case QEvalsListModel.RenameEval:
                return true

            case QEvalsListModel.AddExistingEvalToEvalSet:
                return false

            case QEvalsListModel.RemoveEvalFromEvalSet:
                return true


            // Grading Category Operations
            case QGradingCriteriaModel.AddGradingCriteria:
                return false

            // Evaluation operations
            case QEvaluationModel.AddCustomTextItem:
                return false

            default:
                console.log("Error: operation not defined: " + operation)
                return false
        }
    }


    function renameStudent(firstName, middleName, lastName, gender)
    {
        wrapper.model.renameStudent(firstName, middleName,
                                    lastName, gender, listOfItems.currentIndex)
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
                dialog.onOkClicked.connect(wrapper.model.addStudent)
                dialog.onOkClicked.connect(wizardContent.close)
            }
        }
    }


    Component {
        id: renameStudentDialog
        AddStudentDialog {
            id: dialog
            explanationText: wrapper.model.getOperationExplanationText(mostRecentOperation, listOfItems.currentIndex)
            startingFirstName: wrapper.model.getStudentFirstName(listOfItems.currentIndex)
            startingMiddleName: wrapper.model.getStudentMiddleName(listOfItems.currentIndex)
            startingLastName: wrapper.model.getStudentLastName(listOfItems.currentIndex)
            startingGender: wrapper.model.getStudentGender(listOfItems.currentIndex)

            Component.onCompleted: {
                dialog.onCanceled.connect(wizardContent.close)
                dialog.onCancelClicked.connect(wizardContent.close)
                dialog.onOkClicked.connect(renameStudent)
                dialog.onOkClicked.connect(wizardContent.close)
            }
        }
    }


    Component {
        id: addCustomTextDialog
        CustomTextItemEditDialog {
            id: dialog
            dialogText: wrapper.model.getOperationExplanationText(mostRecentOperation, listOfItems.currentIndex)
            acceptButtonText: "OK"

            Component.onCompleted:
            {
                dialog.onCanceled.connect(wizardContent.close)
                dialog.onCancelClicked.connect(wizardContent.close)
                dialog.onAcceptedClicked.connect(wrapper.model.addCustomTextItem)
                dialog.onAcceptedClicked.connect(wizardContent.close)
            }
        }
    }


    Component {
        id: createEvalSetFromCourseDialog
        CreateEvalSetDialog {
            id: dialog
            explanationText: wrapper.model.getOperationExplanationText(mostRecentOperation, listOfItems.currentIndex)
            stringList: mostRecentItemChooserList

            Component.onCompleted:
            {
                dialog.onCanceled.connect(wizardContent.close)
                dialog.onCancelClicked.connect(wizardContent.close)
                //dialog.onOkClicked.connect()
                dialog.onOkClicked.connect(wizardContent.close)
            }
        }
    }


    Component {
        id: createEvalSetFromEvalSetDialog
        CreateEvalSetDialog {
            id: dialog
            explanationText: wrapper.model.getOperationExplanationText(mostRecentOperation, listOfItems.currentIndex)
            stringList: mostRecentItemChooserList

            Component.onCompleted:
            {
                dialog.onCanceled.connect(wizardContent.close)
                dialog.onCancelClicked.connect(wizardContent.close)
                //dialog.onAcceptedClicked.connect(wrapper.model.addCustomTextItem)
                dialog.onAcceptedClicked.connect(wizardContent.close)
            }
        }
    }


    // Generic components
    Component {
        id: addItemDialog
        SingleLineTextEditDialog {
            id: dialog
            explanationText: wrapper.model.getOperationExplanationText(mostRecentOperation, listOfItems.currentIndex)

            Component.onCompleted: {
                dialog.onCanceled.connect(wizardContent.close)
                dialog.onCancelClicked.connect(wizardContent.close)
                dialog.onOkClicked.connect(wrapper.model.addItem)
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
