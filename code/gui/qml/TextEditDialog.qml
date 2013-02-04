import QtQuick 2.0

Dialog {
    property string startingText
    property string explanationText
    property int textInputWidth: 300
    property int textInputHeight: 100
    property bool isModifyVisible: true
    property Component optionalItem

    signal addClicked(string newText)
    signal modifyClicked(string newText)
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
                }
            }

            Loader {
                sourceComponent: optionalItem
            }

            Row {
                anchors.right: parent.right
                spacing: 15

                TextButton {
                    id: addButton
                    text: "Add New"
                    onClicked: addClicked(question.text)
                }

                TextButton {
                    id: modifyButton
                    text: "Modify Existing"
                    onClicked: modifyClicked(question.text)
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
