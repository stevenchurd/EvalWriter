import QtQuick 2.0
import QtQuick.Layouts 1.0

Rectangle {
    id: wrapper

    property alias source: dialogContent.source
    property alias sourceComponent: dialogContent.sourceComponent
    property string headerText: ""
    property string submitButtonText: "OK"
    property bool cancelButtonEnabled: false
    property string cancelButtonText: "Cancel"
    property color dialogTextColor: "#DDDDDD"

    signal canceled
    signal submitClick
    signal close

    Keys.onEscapePressed: close()

    anchors.centerIn: parent
    height: screenContainer.height
    width: ((dialogContent.width > dialogTitle.width) ? dialogContent.width : dialogTitle.width) + 50

    color: "#444444"

    Rectangle {
        id: highlight
        width: 1
        height: parent.height
        anchors.right: parent.right
        color: "#33AAEE"
    }

    ColumnLayout {
        anchors.fill: parent

        IconButton {
            id: backButton

            icon: "\uf0a8"
            iconColor: "#BBBBBB"
            hoverColor: "#CCCCCC"
            pressedColor: "#DDDDDD"
            smooth: true
            size: 36
            onClicked: close()
        }

        Text {
            id: dialogTitle

            anchors.left: parent.left
            anchors.margins: 20
            font.pointSize: 18
            font.bold: true
            color: "#FFFFFF"
            text: headerText
        }

        Loader {
            id: dialogContent
            Layout.alignment: Qt.AlignTop
            Layout.fillHeight: true
            anchors.left: parent.left
            anchors.margins: 20
            focus: true
            clip: true
        }

        Rectangle {
            id: decorativeLine
            height: 1
            width: parent.width - 20
            Layout.alignment: Qt.AlignHCenter
            anchors.margins: 20

            color: "#999999"
        }

        Rectangle {
            id: buttonRow
            height: 50
            width: parent.width
            color: "transparent"
            Layout.alignment: Qt.AlignBottom | Qt.AlignVCenter

            RowLayout {
                anchors.verticalCenter: parent.verticalCenter
                anchors.right: parent.right
                anchors.rightMargin: 20
                spacing: 10

                TextButton {
                    id: submitButton
                    text: submitButtonText
                    onClicked: submitClick()
                }

                TextButton {
                    id: cancelButton
                    text: cancelButtonText
                    enabled: cancelButtonEnabled
                    visible: cancelButtonEnabled
                    onClicked: canceled()
                }
            }
        }
    }

    function giveTabControlAfterLastElement()
    {
        console.log("last element tabbed")
    }
}
