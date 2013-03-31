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

    clip: true

    ListView {
        id: listOfItems
        height: parent.height
        width: parent.width - listOperationsContainer.width
        model: wrapper.model

        highlight: Rectangle {
            width: (listOfItems.width > 400) ? 400 : listOfItems.width
            color: "lightsteelblue"
        }

        delegate: MouseArea {
            id: delegateWrapper
            height: 60
            // TODO: work on resizing objects eventually
            width: listOfItems.width > 400 ? 400 : listOfItems.width

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

    Rectangle {
        id: listOperationsContainer
        height: parent.height
        width: 100
        anchors.left: listOfItems.right
        color: "red"

        ListModel {
            id: operationsModel
        }

        ListView {
            anchors.fill: parent
            anchors.margins: 5
            spacing: 5
            model: operationsModel
            delegate: TextButton {
                text: operationText
                onClicked: {
                    wizardContent.sourceComponent = componentToDisplay
                    wizardContent.show()
                }
            }
        }
    }

    Component.onCompleted: {
        console.log(wrapper.model.getSubModelOperations())
        fillListOperationsModel()
    }


    function fillListOperationsModel()
    {
        var supportedOperations = wrapper.model.getSubModelOperations()
        operationsModel.clear()

        for(var i = 0; i < supportedOperations.length; i++)
        {
            operationsModel.append({"operationText": JsUtil.getOperationString(supportedOperations[i]),
                                    "componentToDisplay": getOperationComponent(supportedOperations[i])})
        }
    }

    function addCourse(newCourseName)
    {
        wrapper.model.addCourse(newCourseName)
    }


    function removeCourse(index)
    {
        console.log("remove course " + index)
    }


    function getOperationComponent(operation)
    {
        switch(operation) {
            case QCoursesListModel.AddCourse:
                return addCourseDialog

            case QCoursesListModel.RemoveCourse:
                return removeCourseDialog

            case QCoursesListModel.RenameCourse:
                return "Rename Class"

            default:
                console.log("No component defined: " + operation)
        }
    }


    // dialog componenets
    Component {
        id: addCourseDialog
        SingleLineTextEditDialog {
            id: dialog
            explanationText: "Add a class:"

            Component.onCompleted: {
                dialog.onCanceled.connect(wizardContent.close)
                dialog.onCancelClicked.connect(wizardContent.close)
                dialog.onOkClicked.connect(addCourse)
                dialog.onOkClicked.connect(wizardContent.close)
            }
        }
    }

    Component {
        id: removeCourseDialog
        YesNoDialog {
            id: dialog
            dialogText: "Do you want to remove the class \"" + displayString + "\"?"

            Component.onCompleted: {
                dialog.onCanceled.connect(wizardContent.close)
                dialog.onNoClicked.connect(wizardContent.close)
                dialog.onYesClicked.connect(removeCourse)
                dialog.onYesClicked.connect(wizardContent.close)
            }
        }
    }

}
