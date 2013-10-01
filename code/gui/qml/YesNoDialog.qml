import QtQuick 2.0

Dialog {
    id: wrapperDialog
    property string dialogText

    signal yesClicked

    submitButtonText: "Yes"
    cancelButtonEnabled: true
    cancelButtonText: "No"

    Component {
        id: yesNoContainer

        Column {
            id: columnWrapper
            spacing: 15

            Connections {
                target: wrapperDialog
                onSubmitted: yesClicked()
                onDialogTextChanged: {
                    question.text = dialogText
                }
            }

            Text {
                id: question
                text: dialogText
                color: dialogTextColor
                renderType: Text.NativeRendering
                anchors.horizontalCenter: parent.horizontalCenter
            }
       }
    }

    sourceComponent: yesNoContainer
}
