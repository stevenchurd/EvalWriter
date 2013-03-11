import QtQuick 2.0

Dialog {
    property string dialogText
    property string startingText
    property string startingTitle
    property int textInputWidth: 300
    property int textInputHeight: 100

    signal editClicked(string newTitle, string newText)
    signal cancelClicked

    Component {
        id: editContainer

        Column {
            spacing: 15

            Text {
                text: dialogText
                renderType: Text.NativeRendering
                anchors.horizontalCenter: parent.horizontalCenter
            }

            Rectangle {
                width: textInputWidth
                height: 25
                border.color: "black"
                clip: true

                TextEdit {
                    id: customTextTitle
                    anchors.fill: parent
                    textMargin: 5

                    wrapMode: TextEdit.NoWrap
                    renderType: TextEdit.NativeRendering
                    text: startingTitle
                    selectByMouse: true
                    selectionColor: "steelblue"
                    focus: false
                    onActiveFocusChanged: if(focus) {selectAll()}
                }
            }

            Rectangle {
                width: textInputWidth
                height: textInputHeight
                border.color: "black"
                clip: true

                TextEdit {
                    id: customTextItem
                    anchors.fill: parent
                    textMargin: 5

                    wrapMode: TextEdit.Wrap
                    renderType: TextEdit.NativeRendering
                    text: startingText
                    cursorVisible: true
                    selectByMouse: true
                    selectionColor: "steelblue"
                    focus: true
                    onActiveFocusChanged: if(focus) {selectAll()}

                    Component.onCompleted: selectAll()
                }
            }

            Row {
                anchors.horizontalCenter: parent.horizontalCenter
                spacing: 15

                TextButton {
                    id: editButton
                    text: "Edit"
                    onClicked: editClicked(customTextTitle.text, customTextItem.text)
                }

                TextButton {
                    id: cancelButton
                    text: "Cancel"
                    onClicked: cancelClicked()
                }
            }
        }
    }

    sourceComponent: editContainer
}
