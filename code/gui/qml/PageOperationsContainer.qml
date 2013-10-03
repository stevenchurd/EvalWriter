import QtQuick 2.0
import CppEnums 1.0

Rectangle {
    id: wrapper
    height: parent.height
    width: 150
    color: "transparent"

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
                var component = getDialogComponent(operation)
                var properties = getDialogProperties(operation)
                var submitAction = getDialogSubmitAction(operation)

                if(submitAction === null)
                {
                    dialogContent.setSourceComponent(component, properties)

                }
                else
                {
                    dialogContent.setSourceComponentWithSubmit(component, properties, submitAction)
                }
                dialogContent.show()
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
                                    //"componentToDisplay": getOperationComponent(supportedOperations[i]),
                                    "operation": supportedOperations[i]})
        }
    }


    function getDialogComponent(operation)
    {
        switch(operation) {
            case QEvalSetsListModel.AddEvalSet:
            case QCoursesListModel.AddCourse:
            case QEvalsListModel.AddEval:
            case QGradingCriteriaModel.AddGradingCriteria:
            case QCoursesListModel.RenameCourse:
            case QEvalSetsListModel.RenameEvalSet:
            case QEvalsListModel.RenameEval:
                return "SingleLineTextInputDialog.qml"

            case QStudentsListModel.AddStudent:
            case QStudentsListModel.RenameStudent:
                return "AddStudentDialog.qml"

            case QCoursesListModel.RemoveCourse:
            case QCoursesListModel.RemoveExistingCourseFromStudent:
            case QEvalSetsListModel.RemoveEvalSet:
            case QStudentsListModel.RemoveStudent:
            case QStudentsListModel.RemoveStudentFromCourse:
            case QEvalsListModel.RemoveEval:
            case QEvalsListModel.RemoveEvalFromEvalSet:
                return "YesNoDialog.qml"

            case QEvalSetsListModel.CreateEvalSetFromCourse:
            case QEvalSetsListModel.CreateEvalSetFromEvalSet:
                return "CreateEvalSetDialog.qml"

            case QCoursesListModel.AddExistingCourseToStudent:
            case QStudentsListModel.AddExistingStudentToCourse:
            case QEvalsListModel.AddExistingEvalToEvalSet:
                return "ListChooserDialog.qml"

            case QEvaluationModel.AddCustomTextItem:
                return "CustomTextItemEditDialog.qml"

            default:
                console.log("getDialogComponent: No component defined: " + operation)
        }
    }


    function getDialogProperties(operation)
    {
        switch(operation)
        {
            case QCoursesListModel.AddCourse:
            case QEvalSetsListModel.AddEvalSet:
            case QEvalsListModel.AddEval:
            case QGradingCriteriaModel.AddGradingCriteria:
                return { "explanationText": wrapper.model.getOperationExplanationText(operation, listOfItems.currentIndex),
                         "headerText": getDialogTitle(operation)}

            case QStudentsListModel.AddStudent:
                return { "explanationText": wrapper.model.getOperationExplanationText(operation, listOfItems.currentIndex),
                         "headerText": "add new student" }

            case QStudentsListModel.RenameStudent:
                return {
                    "explanationText": wrapper.model.getOperationExplanationText(operation, listOfItems.currentIndex),
                    "headerText": "rename student",
                    "startingFirstName": wrapper.model.getStudentFirstName(listOfItems.currentIndex),
                    "startingMiddleName": wrapper.model.getStudentMiddleName(listOfItems.currentIndex),
                    "startingLastName": wrapper.model.getStudentLastName(listOfItems.currentIndex),
                    "startingGender": wrapper.model.getStudentGender(listOfItems.currentIndex)
                }

            case QCoursesListModel.RemoveCourse:
            case QCoursesListModel.RemoveExistingCourseFromStudent:
            case QEvalSetsListModel.RemoveEvalSet:
            case QStudentsListModel.RemoveStudent:
            case QStudentsListModel.RemoveStudentFromCourse:
            case QEvalsListModel.RemoveEval:
            case QEvalsListModel.RemoveEvalFromEvalSet:
                return { "dialogText": wrapper.model.getOperationExplanationText(operation, listOfItems.currentIndex),
                         "headerText": getDialogTitle(operation) }

            case QCoursesListModel.RenameCourse:
            case QEvalSetsListModel.RenameEvalSet:
            case QEvalsListModel.RenameEval:
                return { "explanationText": wrapper.model.getOperationExplanationText(operation, listOfItems.currentIndex),
                         "startingText": listOfItems.currentItem.itemString,
                         "headerText": getDialogTitle(operation) }

            case QCoursesListModel.AddExistingCourseToStudent:
            case QStudentsListModel.AddExistingStudentToCourse:
            case QEvalsListModel.AddExistingEvalToEvalSet:
                return { "explanationText": wrapper.model.getOperationExplanationText(operation, listOfItems.currentIndex),
                         "stringList": wrapper.model.getOptionListForOperation(operation),
                         "operation": operation,
                         "headerText": getDialogTitle(operation)}

            case QEvaluationModel.AddCustomTextItem:
                return { "explanationText": wrapper.model.getOperationExplanationText(operation, listOfItems.currentIndex),
                         "headerText": getDialogTitle(operation) }

            case QEvalSetsListModel.CreateEvalSetFromEvalSet:
            case QEvalSetsListModel.CreateEvalSetFromCourse:
                return { "explanationText": wrapper.model.getOperationExplanationText(operation, listOfItems.currentIndex),
                    "stringList": wrapper.model.getOptionListForOperation(operation),
                    "operation": operation,
                    "headerText": getDialogTitle(operation) }


            default:
                console.log("getDialogProperties: No component defined: " + operation)
        }
    }


    function getDialogSubmitAction(operation)
    {
        switch(operation)
        {
            case QStudentsListModel.AddStudent:
                return wrapper.model.addStudent

            case QStudentsListModel.RenameStudent:
                return renameStudent

            case QEvaluationModel.AddCustomTextItem:
                return wrapper.model.addCustomTextItem

            case QEvalSetsListModel.CreateEvalSetFromCourse:
            case QEvalSetsListModel.CreateEvalSetFromEvalSet:
                return wrapper.model.createEvalSet

            case QEvalSetsListModel.AddEvalSet:
            case QCoursesListModel.AddCourse:
            case QEvalsListModel.AddEval:
            case QGradingCriteriaModel.AddGradingCriteria:
                return wrapper.model.addItem

            case QCoursesListModel.RenameCourse:
            case QEvalSetsListModel.RenameEvalSet:
            case QEvalsListModel.RenameEval:
                return renameItem

            case QCoursesListModel.RemoveCourse:
            case QCoursesListModel.RemoveExistingCourseFromStudent:
            case QEvalSetsListModel.RemoveEvalSet:
            case QStudentsListModel.RemoveStudent:
            case QStudentsListModel.RemoveStudentFromCourse:
            case QEvalsListModel.RemoveEval:
            case QEvalsListModel.RemoveEvalFromEvalSet:
                return removeItem

            case QCoursesListModel.AddExistingCourseToStudent:
            case QStudentsListModel.AddExistingStudentToCourse:
            case QEvalsListModel.AddExistingEvalToEvalSet:
                return wrapper.model.optionListSelection

            default:
                console.log("getDialogSubmitAction: No component defined: " + operation)

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

    function getDialogTitle(operation)
    {
        switch(operation)
        {
            case QCoursesListModel.AddExistingCourseToStudent:
                return "add student to class"

            case QCoursesListModel.AddCourse:
                return "add new class"

            case QCoursesListModel.RemoveCourse:
                return "remove class"

            case QCoursesListModel.RenameCourse:
                return "rename class"

            case QStudentsListModel.AddExistingStudentToCourse:
                return "add student to class"

            case QStudentsListModel.RemoveStudentFromCourse:
                return "remove student from class"

            case QStudentsListModel.RemoveStudent:
                return "remove student"

            case QEvalsListModel.AddExistingEvalToEvalSet:
                return "add evaluation to set"

            case QEvalsListModel.AddEval:
                return "add evaluation"

            case QEvalsListModel.RemoveEval:
                return "remove evaluation"

            case QEvalsListModel.RenameEval:
                return "rename evaluation"

            case QEvalSetsListModel.CreateEvalSetFromCourse:
                return "create evaluation set from class"

            case QEvalSetsListModel.CreateEvalSetFromEvalSet:
                return "duplicate evaluation set"

            case QEvalSetsListModel.AddEvalSet:
                return "add new evaluation set"

            case QEvalSetsListModel.RenameEvalSet:
                return "rename evaluation set"

            case QEvalSetsListModel.RemoveEvalSet:
                return "remove evaluation set"

            case QEvaluationModel.AddCustomTextItem:
                return "add custom text item"

            case QEvalsListModel.RemoveEvalFromEvalSet:
                return "remove evaluation from set"

            case QGradingCriteriaModel.AddGradingCriteria:
                return "add grading category"

            default:
                console.log("getDialogTitle: operation not defined: " + operation)
                return String(operation)
        }
    }


    function isOperationIndexDependent(operation)
    {
        switch(operation) {
            case QCoursesListModel.AddCourse:
            case QCoursesListModel.AddExistingCourseToStudent:
            case QEvalSetsListModel.CreateEvalSetFromCourse:
            case QEvalSetsListModel.CreateEvalSetFromEvalSet:
            case QEvalSetsListModel.AddEvalSet:
            case QStudentsListModel.AddStudent:
            case QStudentsListModel.AddExistingStudentToCourse:
            case QEvalsListModel.AddEval:
            case QEvalsListModel.AddExistingEvalToEvalSet:
            case QGradingCriteriaModel.AddGradingCriteria:
            case QEvaluationModel.AddCustomTextItem:
                return false

            case QCoursesListModel.RemoveCourse:
            case QCoursesListModel.RenameCourse:
            case QCoursesListModel.RemoveExistingCourseFromStudent:
            case QEvalSetsListModel.RemoveEvalSet:
            case QEvalSetsListModel.RenameEvalSet:
            case QStudentsListModel.RemoveStudent:
            case QStudentsListModel.RenameStudent:
            case QStudentsListModel.RemoveStudentFromCourse:
            case QEvalsListModel.RemoveEval:
            case QEvalsListModel.RenameEval:
            case QEvalsListModel.RemoveEvalFromEvalSet:
                return true

            default:
                console.log("isOperationIndexDependent: operation not defined: " + operation)
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
}
