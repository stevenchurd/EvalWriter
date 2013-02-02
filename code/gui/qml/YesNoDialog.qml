import QtQuick 2.0

Dialog {
    property string dialogText

    signal yesClicked
    signal noClicked

    Component {
        id: yesNoContainer

        Column {

            height: 100
            width: 200
            spacing: 15

            anchors.centerIn: parent

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
                }

                TextButton {
                    id: noButton
                    text: "No"
                }
            }
        }
    }

    sourceComponent: yesNoContainer
}
