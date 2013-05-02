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
                id: textInputRect

                width: textInputWidth
                height: textInputHeight
                color: "#EEEEEE"
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
                    onAccepted: trySubmit()
                }
            }

            Row {
                anchors.right: parent.right
                spacing: 15

                TextButton {
                    id: okButton
                    text: "OK"
                    onClicked: trySubmit()
                }

                TextButton {
                    id: cancelButton
                    text: "Cancel"
                    onClicked: cancelClicked()
                }
            }

            function trySubmit()
            {
                question.text = question.text.trim()
                if(isValid(question.text))
                {
                    textInputRect.border.color = "transparent"
                    okClicked(question.text)
                }
                else
                {
                    textInputRect.border.color = "red"
                }
            }
        }
    }

    function isValid(text)
    {
        if(text.length > 0)
            return true
        else
            return false
    }

    sourceComponent: textInputComponent
}
