import QtQuick 2.1
import QtQuick.Controls 1.0

Dialog {
    id: wrapperDialog
    property string dialogText
    property string startingText
    property string startingTitle
    property int textInputWidth: 300
    property int textInputHeight: 100
    property string acceptButtonText

    signal acceptedClicked(string newTitle, string newText)
    signal cancelClicked

    headerText: "add custom text item"
    cancelButtonEnabled: true
    cancelButtonText: "Cancel"

    Component {
        id: editContainer

        Column {
            id: columnWrapper
            spacing: 5

            Connections {
                target: wrapperDialog
                onSubmitted: columnWrapper.trySubmit()
            }

            Text {
                text: dialogText
                color: dialogTextColor
                renderType: Text.NativeRendering
            }

            Rectangle {
                id: spacingRectangle
                height: 10
                width: 5
                color: "transparent"
            }

            Text {
                text: "Title:"
                color: dialogTextColor
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
                color: dialogTextColor
                renderType: Text.NativeRendering
            }

            Rectangle {
                id: bodyRect

                width: textInputWidth
                height: textInputHeight
                color: "#EEEEEE"
                clip: true

                TextArea {
                    id: customTextItem
                    anchors.fill: parent
                    backgroundVisible: false
                    tabChangesFocus: true

                    wrapMode: TextEdit.Wrap
                    text: startingText
                    selectByMouse: true
                    //selectionColor: "steelblue"

                    Keys.onTabPressed: acceptButton.focus = true

                    onActiveFocusChanged: if(focus) {selectAll()}
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
