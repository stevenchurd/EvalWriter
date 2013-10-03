import QtQuick 2.0
import QtQuick.Controls 1.0

Dialog {
    id: dialogWrapper

    property string startingText
    property string explanationText
    property int currentLevel
    property int textInputHeight: 100
    property bool isModifyVisible: true

    signal submitted(string newText, int level)
    signal secondarySubmitted(string newText, int level)

    submitButtonText: "OK"
    secondarySubmitButtonEnabled: isModifyVisible
    secondarySubmitButtonText: "Modify Existing"
    cancelButtonEnabled: true
    cancelButtonText: "Cancel"

    Component {
        id: textInputComponent

        Column {
            id: columnWrapper
            spacing: 15

            Connections {
                target: dialogWrapper
                onSubmitClick: columnWrapper.trySubmit()
                onSecondarySubmitClick: columnWrapper.trySecondarySubmit()
            }

            Text {
                text: explanationText
                renderType: Text.NativeRendering
            }

            Rectangle {
                width: parent.width
                height: textInputHeight
                color: "#EEEEEE"
                clip: true

                TextArea {
                    id: question
                    anchors.fill: parent

                    wrapMode: TextEdit.Wrap
                    text: startingText
                    selectByMouse: true
                    focus: true
                    tabChangesFocus: true
                    backgroundVisible: false

                    Component.onCompleted: selectAll()
                }
            }

            Rectangle {
                height: 110
                width: parent.width
                color: "transparent"

                ListModel {
                    id: criteriaLevelModel

                    ListElement { level: "Excellent" }
                    ListElement { level: "Above Average" }
                    ListElement { level: "Average" }
                    ListElement { level: "Below Average" }
                    ListElement { level: "Poor" }
                }

                CommonListView {
                    id: criteriaLevelSelector
                    anchors.fill: parent
                    currentIndex: currentLevel
                    model: criteriaLevelModel
                    delegate: CommonListDelegate {
                        text: level
                    }
                }
            }

            function trySubmit()
            {
                //TODO add checking here
                submitted(question.text, criteriaLevelSelector.currentIndex)
                close()
            }

            function trySecondarySubmit()
            {
                //TODO add checking here
                secondarySubmitted(question.text, criteriaLevelSelector.currentIndex)
                close()
            }
        }
    }

    sourceComponent: textInputComponent
}
