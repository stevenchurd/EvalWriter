import QtQuick 2.0

Dialog {
    property string startingText
    property string explanationText
    property int textInputWidth: 300
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
                width: textInputWidth
                height: textInputHeight
                border.color: "black"
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
                height: 100
                width: parent.width
                CommonListView {
                    id: criteriaLevelSelector
                    anchors.fill: parent
                    model: 5
                    delegate: CommonListDelegate {
                        itemsToHold: Text {
                            text: {
                                switch(index+1)
                                {
                                    case 1:
                                        return "Excellent"
                                    case 2:
                                        return "Above Average"
                                    case 3:
                                        return "Average"
                                    case 4:
                                        return "Below Average"
                                    case 5:
                                        return "Poor"
                                    default:
                                        return "Invalid"
                                }
                            }
                            renderType: Text.NativeRendering
                        }
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
