import QtQuick 2.0

Dialog {
    id: wrapper

    property string explanationText
    property var stringList
    property int operation
    property int dialogWidth: 300

    signal submitted(int itemSelected, int operation, string name, string prefix)

    cancelButtonEnabled: true
    cancelButtonText: "Cancel"
    submitButtonText: "Create"

    Component {
        id: itemChooser

        Column {
            id: columnWrapper
            width: wrapper.dialogWidth
            spacing: 15

            Connections {
                target: wrapper
                onSubmitClick: columnWrapper.trySubmit()
            }

            Text {
                width: parent.width
                text: explanationText
                color: dialogTextColor
                renderType: Text.NativeRendering
                wrapMode: Text.WordWrap
            }

            Column {
                width: wrapper.dialogWidth
                Text {
                    width: parent.width
                    text: "Choose item to base new Evaluation Set on:"
                    color: dialogTextColor
                    renderType: Text.NativeRendering
                    wrapMode: Text.WordWrap
                }

                Rectangle {
                    width: parent.width
                    height: itemSelectorList.height
                    color: "transparent"

                    CommonListView {
                        id: itemSelectorList
                        numElementsVisible: 5
                        width: parent.width - (scrollbar.width + 5)
                        clip: true
                        currentIndex: 0
                        model: stringList
                        delegate: CommonListDelegate {
                            text: modelData
                        }
                    }

                    Scrollbar {
                        id: scrollbar
                        target: itemSelectorList
                    }
                }
            }

            Column {
                width: wrapper.dialogWidth
                Text {
                    width: parent.width
                    text: "Enter the name of the new Evaluation Set:"
                    color: dialogTextColor
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

                        onFocusChanged: selectAll()
                        onAccepted: trySubmit()
                    }
                }
            }

            Column {
                width: wrapper.dialogWidth
                Text {
                    width: parent.width
                    text: "Enter the prefix to use for each newly created Evaluation:"
                    color: dialogTextColor
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

                        onFocusChanged: selectAll()
                        onAccepted: trySubmit()
                    }
                }
            }

            Column {
                width: wrapper.dialogWidth
                Text {
                    width: parent.width
                    text: "Sample evaluation name:"
                    color: dialogTextColor
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

            function trySubmit()
            {
                evalNamePrefixTextInput.text = evalNamePrefixTextInput.text.trim()
                evalSetNameTextInput.text = evalSetNameTextInput.text.trim()

                evalSetNameRect.border.color = "transparent"
                evalNamePrefixRect.border.color = "transparent"

                if(evalNamePrefixTextInput.text.length > 0 &&
                        evalSetNameTextInput.text.length > 0)
                {
                    submitted(itemSelectorList.currentIndex,
                              wrapper.operation,
                              evalSetNameTextInput.text,
                              evalNamePrefixTextInput.text)
                    close()
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
