import QtQuick 2.0

Dialog {
    property string startingText
    property string explanationText
    property int textInputWidth: 300
    property int textInputHeight: 25

    signal okClicked(string newText)
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

                TextInput {
                    id: question
                    anchors.fill: parent
                    anchors.margins: 5

                    renderType: TextInput.NativeRendering
                    text: startingText
                    cursorVisible: true
                    selectByMouse: true
                    selectionColor: "steelblue"
                    focus: true

                    Component.onCompleted: selectAll()
                    onAccepted: okClicked(displayText)
                }
            }

            Row {
                anchors.right: parent.right
                spacing: 15

                TextButton {
                    id: okButton
                    text: "OK"
                    onClicked: okClicked(question.text)
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
