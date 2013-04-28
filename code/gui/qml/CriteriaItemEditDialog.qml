import QtQuick 2.0

Dialog {
    property string startingText
    property string explanationText
    property int currentLevel
    property int textInputHeight: 100
    property bool isModifyVisible: true

    signal addClicked(string newText, int level)
    signal modifyClicked(string newText, int level)
    signal cancelClicked

    Component {
        id: textInputComponent

        Column {
            spacing: 15

            Text {
                text: explanationText
                renderType: Text.NativeRendering
            }

            Rectangle {
                width: parent.width
                height: textInputHeight
                color: "#EEEEEE"
                clip: true

                TextEdit {
                    id: question
                    anchors.fill: parent
                    textMargin: 5

                    wrapMode: TextEdit.Wrap
                    renderType: TextEdit.NativeRendering
                    text: startingText
                    cursorVisible: true
                    selectByMouse: true
                    selectionColor: "steelblue"
                    focus: true

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

            Row {
                anchors.right: parent.right
                spacing: 15

                TextButton {
                    id: addButton
                    text: "Add New"
                    onClicked: addClicked(question.text, criteriaLevelSelector.currentIndex)
                }

                TextButton {
                    id: modifyButton
                    text: "Modify Existing"
                    onClicked: modifyClicked(question.text, criteriaLevelSelector.currentIndex)
                    visible: isModifyVisible
                }

                TextButton {
                    id: cancelButton
                    text: "Cancel"
                    onClicked: cancelClicked()
                }
            }
        }
    }

    sourceComponent: textInputComponent
}
