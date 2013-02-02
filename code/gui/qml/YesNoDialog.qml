import QtQuick 2.0

Dialog {
    property string dialogText

    signal yesClicked
    signal noClicked

    Component {
        id: yesNoContainer

        Column {
            spacing: 15

            Text {
                id: question
                text: dialogText
                renderType: Text.NativeRendering
                anchors.horizontalCenter: parent.horizontalCenter
            }

            Row {
                anchors.horizontalCenter: parent.horizontalCenter
                spacing: 15

                TextButton {
                    id: yesButton
                    text: "Yes"
                    onClicked: yesClicked()
                }

                TextButton {
                    id: noButton
                    text: "No"
                    onClicked: noClicked()
                }
            }
        }
    }

    sourceComponent: yesNoContainer
}
