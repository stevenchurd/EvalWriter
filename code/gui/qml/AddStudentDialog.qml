import QtQuick 2.0

Dialog {
    property string startingFirstName
    property string startingMiddleName
    property string startingLastName
    property int startingGender
    property string explanationText
    property int textInputWidth: 300
    property int textInputHeight: 25

    signal okClicked(string firstName, string middleName, string lastName, int gender)
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
                        color: "#EEEEEE"
                        clip: true

                        TextInput {
                            id: firstName
                            anchors.fill: parent
                            anchors.margins: 5

                            Keys.onTabPressed: middleName.focus = true

                            renderType: TextInput.NativeRendering
                            text: startingFirstName
                            cursorVisible: true
                            selectByMouse: true
                            selectionColor: "steelblue"
                            focus: true

                            Component.onCompleted: selectAll()
                            onAccepted: trySubmit()
                            onFocusChanged: selectAll()
                        }
                    }
                }

                Column {
                    Text {
                        text: "Middle Initial"
                        renderType: Text.NativeRendering
                    }

                    Rectangle {
                        id: middleNameInputRect

                        width: textInputWidth/3
                        height: textInputHeight
                        color: "#EEEEEE"
                        clip: true

                        TextInput {
                            id: middleName
                            anchors.fill: parent
                            anchors.margins: 5

                            Keys.onTabPressed: lastName.focus = true
                            maximumLength: 1

                            renderType: TextInput.NativeRendering
                            text: startingMiddleName
                            selectByMouse: true
                            selectionColor: "steelblue"

                            onFocusChanged: selectAll()
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
                        color: "#EEEEEE"
                        clip: true

                        TextInput {
                            id: lastName
                            anchors.fill: parent
                            anchors.margins: 5

                            Keys.onTabPressed: genderList.focus = true

                            renderType: TextInput.NativeRendering
                            text: startingLastName
                            selectByMouse: true
                            selectionColor: "steelblue"

                            onFocusChanged: selectAll()
                            onAccepted: trySubmit()
                        }
                    }
                }
            }

            Rectangle {
                height: 48
                width: parent.width
                color: "transparent"

                ListModel {
                    id: genderModel
                    ListElement { name: "Female" }
                    ListElement { name: "Male" }
                }

                CommonListView {
                    id: genderList
                    anchors.fill: parent

                    Keys.onTabPressed: okButton.focus = true
                    currentIndex: startingGender
                    model: genderModel
                    delegate: CommonListDelegate {
                        text: name
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
                    firstNameInputRect.border.color = "transparent"
                }
                else
                {
                    firstNameInputRect.border.color = "red"
                    valid = false
                }

                if(isValid(lastName.text))
                {
                    lastNameInputRect.border.color = "transparent"
                }
                else
                {
                    lastNameInputRect.border.color = "red"
                    valid = false
                }

                // if all the checks passed, we can submit
                if(valid == true)
                {
                    okClicked(firstName.text, middleName.text, lastName.text, genderList.currentIndex)
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
