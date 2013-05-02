import QtQuick 2.0

Dialog {
    id: wrapper

    property string explanationText
    property var stringList
    property int operation
    property int dialogWidth: 300

    signal okClicked(int itemSelected, int operation, string name, string prefix)
    signal cancelClicked

    Component {
        id: itemChooser

        Column {
            width: wrapper.dialogWidth
            spacing: 15

            Text {
                width: parent.width
                text: explanationText
                renderType: Text.NativeRendering
                wrapMode: Text.WordWrap
            }

            Column {
                width: wrapper.dialogWidth
                Text {
                    width: parent.width
                    text: "Choose item to base new Evaluation Set on:"
                    renderType: Text.NativeRendering
                    wrapMode: Text.WordWrap
                }

                Rectangle {
                    width: parent.width
                    height: itemSelectorList.contentHeight + 10
                    color: "transparent"
                    CommonListView {
                        id: itemSelectorList
                        anchors.fill: parent
                        currentIndex: 0
                        model: stringList
                        delegate: CommonListDelegate {
                            text: modelData
                        }
                    }
                }
            }

            Column {
                width: wrapper.dialogWidth
                Text {
                    width: parent.width
                    text: "Enter the name of the new Evaluation Set:"
                    renderType: Text.NativeRendering
                    wrapMode: Text.WordWrap
                }

                Rectangle {
                    id: evalSetNameRect

                    width: wrapper.dialogWidth
                    height: 25
                    color: "#EEEEEE"
                    clip: true

                    TextInput {
                        id: evalSetNameTextInput
                        anchors.fill: parent
                        anchors.margins: 5

                        renderType: TextInput.NativeRendering
                        selectByMouse: true
                        selectionColor: "steelblue"

                        onAccepted: trySubmit()
                    }
                }
            }

            Column {
                width: wrapper.dialogWidth
                Text {
                    width: parent.width
                    text: "Enter the prefix to use for each newly created Evaluation:"
                    renderType: Text.NativeRendering
                    wrapMode: Text.WordWrap
                }

                Rectangle {
                    id: evalNamePrefixRect

                    width: wrapper.dialogWidth
                    height: 25
                    color: "#EEEEEE"
                    clip: true

                    TextInput {
                        id: evalNamePrefixTextInput
                        anchors.fill: parent
                        anchors.margins: 5

                        renderType: TextInput.NativeRendering
                        selectByMouse: true
                        selectionColor: "steelblue"

                        onAccepted: trySubmit()
                    }
                }
            }

            Column {
                width: wrapper.dialogWidth
                Text {
                    width: parent.width
                    text: "Sample evaluation name:"
                    renderType: Text.NativeRendering
                    wrapMode: Text.WordWrap
                }

                Rectangle {
                    id: sampleRect

                    width: wrapper.dialogWidth
                    height: 25
                    color: "#CCCCCC"
                    clip: true

                    Text {
                        id: sampleText
                        anchors.fill: parent
                        anchors.margins: 5
                        // eval name format:
                        // evalPrefix: John Smith
                        text: evalNamePrefixTextInput.text + ": Alex Trebek"

                        renderType: TextInput.NativeRendering
                    }
                }
            }
            Row {
                spacing: 15

                TextButton {
                    id: okButton
                    text: "Create"
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
                evalNamePrefixTextInput.text = evalNamePrefixTextInput.text.trim()
                evalSetNameTextInput.text = evalSetNameTextInput.text.trim()

                evalSetNameRect.border.color = "transparent"
                evalNamePrefixRect.border.color = "transparent"

                if(evalNamePrefixTextInput.text.length > 0 &&
                        evalSetNameTextInput.text.length > 0)
                {
                    okClicked(itemSelectorList.currentIndex,
                              wrapper.operation,
                              evalSetNameTextInput.text,
                              evalNamePrefixTextInput.text);
                }

                if(evalSetNameTextInput.text.length <= 0)
                {
                    evalSetNameRect.border.color = "red"
                }

                if(evalNamePrefixTextInput.text.length <= 0)
                {
                    evalNamePrefixRect.border.color = "red"
                }
            }
        }
    }

    sourceComponent: itemChooser
}
