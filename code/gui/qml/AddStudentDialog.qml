import QtQuick 2.0

Dialog {
    property string startingText
    property string explanationText
    property int textInputWidth: 300
    property int textInputHeight: 25

    signal okClicked(string firstName, string middleName, string lastName)
    signal cancelClicked

    Component {
        id: textInputComponent

        Column {
            spacing: 15

            Text {
                text: explanationText
                renderType: Text.NativeRendering
            }

            Row {
                spacing: 5
                Column {
                    Text {
                        text: "First name"
                        renderType: Text.NativeRendering
                    }

                    Rectangle {
                        id: firstNameInputRect

                        width: textInputWidth/3
                        height: textInputHeight
                        border.color: "black"
                        clip: true

                        TextInput {
                            id: firstName
                            anchors.fill: parent
                            anchors.margins: 5

                            Keys.onTabPressed: middleName.focus = true

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
                }

                Column {
                    Text {
                        text: "Middle Name"
                        renderType: Text.NativeRendering
                    }

                    Rectangle {
                        id: middleNameInputRect

                        width: textInputWidth/3
                        height: textInputHeight
                        border.color: "black"
                        clip: true

                        TextInput {
                            id: middleName
                            anchors.fill: parent
                            anchors.margins: 5

                            Keys.onTabPressed: lastName.focus = true

                            renderType: TextInput.NativeRendering
                            text: startingText
                            selectByMouse: true
                            selectionColor: "steelblue"

                            onAccepted: trySubmit()
                        }
                    }
                }

                Column {
                    Text {
                        text: "Last Name"
                        renderType: Text.NativeRendering
                    }

                    Rectangle {
                        id: lastNameInputRect

                        width: textInputWidth/3
                        height: textInputHeight
                        border.color: "black"
                        clip: true

                        TextInput {
                            id: lastName
                            anchors.fill: parent
                            anchors.margins: 5

                            Keys.onTabPressed: okButton.focus = true

                            renderType: TextInput.NativeRendering
                            text: startingText
                            selectByMouse: true
                            selectionColor: "steelblue"

                            onAccepted: trySubmit()
                        }
                    }
                }
            }

            Row {
                anchors.right: parent.right
                spacing: 15

                TextButton {
                    id: okButton
                    Keys.onTabPressed: cancelButton.focus = true
                    text: "OK"
                    onClicked: trySubmit()
                }

                TextButton {
                    id: cancelButton
                    Keys.onTabPressed: firstName.focus = true
                    text: "Cancel"
                    onClicked: cancelClicked()
                }
            }

            function trySubmit()
            {
                var valid = true
                firstName.text = firstName.text.trim()
                middleName.text = middleName.text.trim()
                lastName.text = lastName.text.trim()

                if(isValid(firstName.text))
                {
                    firstNameInputRect.border.color = "black"
                }
                else
                {
                    firstNameInputRect.border.color = "red"
                    valid = false
                }

                if(isValid(middleName.text))
                {
                    middleNameInputRect.border.color = "black"
                }
                else
                {
                    middleNameInputRect.border.color = "red"
                    valid = false
                }

                if(isValid(lastName.text))
                {
                    lastNameInputRect.border.color = "black"
                }
                else
                {
                    lastNameInputRect.border.color = "red"
                    valid = false
                }

                // if all the checks passed, we can submit
                if(valid == true)
                {
                    okClicked(firstName.text, middleName.text, lastName.text)
                }
            }

            function isValid(text)
            {
                if(text.length > 0)
                    return true
                else
                    return false
            }
        }
    }


    sourceComponent: textInputComponent
}
