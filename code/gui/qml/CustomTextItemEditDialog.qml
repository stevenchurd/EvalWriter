import QtQuick 2.0

Dialog {
    property string dialogText
    property string startingText
    property string startingTitle
    property int textInputWidth: 300
    property int textInputHeight: 100
    property string acceptButtonText

    signal acceptedClicked(string newTitle, string newText)
    signal cancelClicked

    Component {
        id: editContainer

        Column {
            spacing: 15

            Text {
                text: dialogText
                renderType: Text.NativeRendering
            }

            Text {
                text: "Title:"
                renderType: Text.NativeRendering
            }

            Rectangle {
                id: titleRect

                width: textInputWidth
                height: 25
                color: "#EEEEEE"
                clip: true

                TextInput {
                    id: customTextTitle
                    anchors.fill: parent
                    anchors.margins: 5

                    renderType: TextInput.NativeRendering
                    text: startingTitle
                    cursorVisible: true
                    selectByMouse: true
                    selectionColor: "steelblue"
                    focus: true

                    Keys.onTabPressed: customTextItem.focus = true

                    onActiveFocusChanged: if(focus) {selectAll()}
                    onAccepted: trySubmit()
                    Component.onCompleted: selectAll()
                }
            }

            Text {
                text: "Custom text to display:"
                renderType: Text.NativeRendering
            }

            Rectangle {
                id: bodyRect

                width: textInputWidth
                height: textInputHeight
                color: "#EEEEEE"
                clip: true

                TextEdit {
                    id: customTextItem
                    anchors.fill: parent
                    textMargin: 5

                    wrapMode: TextEdit.Wrap
                    renderType: TextEdit.NativeRendering
                    text: startingText
                    selectByMouse: true
                    selectionColor: "steelblue"

                    Keys.onTabPressed: acceptButton.focus = true

                    onActiveFocusChanged: if(focus) {selectAll()}
                }
            }

            Row {
                anchors.horizontalCenter: parent.horizontalCenter
                spacing: 15

                TextButton {
                    id: acceptButton
                    text: acceptButtonText

                    Keys.onTabPressed: cancelButton.focus = true
                    Keys.onEnterPressed: trySubmit()

                    onClicked: trySubmit()
                }

                TextButton {
                    id: cancelButton
                    text: "Cancel"

                    Keys.onTabPressed: customTextTitle.focus = true
                    Keys.onEnterPressed: cancelClicked()
                    onClicked: cancelClicked()
                }
            }

            function trySubmit()
            {
                var accept = true

                customTextTitle.text = customTextTitle.text.trim()
                customTextItem.text = customTextItem.text.trim()

                if(customTextTitle.text.length <= 0)
                {
                    accept = false
                    titleRect.border.color = "red"
                }
                else
                {
                    titleRect.border.color = "transparent"
                }

                if(customTextItem.text.length <= 0)
                {
                    accept = false
                    bodyRect.border.color = "red"
                }
                else
                {
                    bodyRect.border.color = "transparent"
                }

                if(accept == true)
                {
                    bodyRect.border.color = "transparent"
                    titleRect.border.color = "transparent"
                    acceptedClicked(customTextTitle.text, customTextItem.text)
                }
            }
        }
    }

    sourceComponent: editContainer
}
