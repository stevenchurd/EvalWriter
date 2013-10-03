import QtQuick 2.0

Dialog {
    property string dialogText

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

    onSubmitClick: close()

    sourceComponent: infoContainer
}
