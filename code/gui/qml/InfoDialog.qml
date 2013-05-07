import QtQuick 2.0

Dialog {
    property string dialogText

    signal closeClicked

    Component {
        id: infoContainer

        Column {
            spacing: 15

            Text {
                text: dialogText
                renderType: Text.NativeRendering
                anchors.horizontalCenter: parent.horizontalCenter
            }

            Row {
                anchors.horizontalCenter: parent.horizontalCenter
                spacing: 15

                TextButton {
                    id: closeButton
                    text: "Close"
                    onClicked: closeClicked()
                }
            }
        }
    }

    sourceComponent: infoContainer
}
