import QtQuick 2.0

Dialog {
    property string dialogText
    property string startingText
    property int textInputWidth: 300
    property int textInputHeight: 100

    signal editClicked(string newText)
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

                    Component.onCompleted: selectAll()
                }
            }

            Row {
                anchors.horizontalCenter: parent.horizontalCenter
                spacing: 15

                TextButton {
                    id: editButton
                    text: "Edit"
                    onClicked: editClicked(customTextItem.text)
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
