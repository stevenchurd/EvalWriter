import QtQuick 2.0

Rectangle {
    id: decorativeRect

    property alias text: criteriaText.text
    property int criteriaLevelIndicator
    property bool buttonsVisible

    signal deleteClicked(int index)
    signal modifyClicked(int index)
    signal itemClicked(int index)

    height: criteriaText.height + 5
    color: "transparent"

    MouseArea {
        anchors.fill: parent
        onClicked: itemClicked(index)
    }

    Row {
        id: rowContainer

        width: parent.width
        spacing: 10

        Rectangle {
            id: indentRect
            width: 40
            height: parent.height
            color: "transparent"
        }

        Rectangle {
            id: levelIndicator
            width: 7
            height: parent.height
            anchors.verticalCenter: parent.verticalCenter

            border.color: "black"
            antialiasing: true
            color: getColor()

            function getColor()
            {
                switch(criteriaLevelIndicator)
                {
                    case 0:
                        return "green"
                    case 1:
                        return "lightgreen"
                    case 2:
                        return "yellow"
                    case 3:
                        return "#ff6666"
                    case 4:
                        return "red"
                    default:
                        break;
                }
            }
            radius: width*.5
        }

        Text {
            id: criteriaText
            width: {
                parent.width -
                        indentRect.width -
                        levelIndicator.width -
                        modifyButton.width -
                        deleteButton.width -
                        (rowContainer.spacing*4)
            }

            font.pointSize: 10
            wrapMode: Text.WordWrap
            renderType: Text.NativeRendering
        }

        TextButton{
            id: modifyButton
            text: "Modify"
            anchors.top: parent.top
            visible: buttonsVisible
            onClicked: modifyClicked(index)
        }

        TextButton{
            id: deleteButton
            text: "Delete"
            anchors.top: parent.top
            visible: buttonsVisible
            onClicked: deleteClicked(index)
        }
    }
}
