import QtQuick 2.0

Dialog {
    property string dialogText

    signal closeClicked

    submitButtonText: "Close"

    Component {
        id: infoContainer

        Text {
            text: dialogText
            color: dialogTextColor
            renderType: Text.NativeRendering
            anchors.horizontalCenter: parent.horizontalCenter
        }
    }

    onSubmitted: closeClicked()

    sourceComponent: infoContainer
}
