import QtQuick 2.0

Dialog {
    id: wrapperDialog
    property string startingText
    property string explanationText
    property int textInputWidth: 300
    property int textInputHeight: 25
    property color dialogTextColor: "#DDDDDD"

    signal okClicked(string newText)
    signal cancelClicked

    Component {
        id: textInputComponent

        Column {
            id: columnWrapper
            spacing: 15

            Connections {
                target: wrapperDialog
                onSubmitted: columnWrapper.trySubmit()
                onStartingTextChanged: {
                    question.text = startingText
                    question.selectAll()
                }
                onExplanationTextChanged: {
                    explanation.text = explanationText
                }
            }

            Text {
                id: explanation
                text: explanationText
                color: dialogTextColor
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

                    onFocusChanged: selectAll()
                    Component.onCompleted: selectAll()
                    onAccepted: trySubmit()
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
