import QtQuick 2.0

Rectangle {
    anchors.fill: parent

    ListView {
        id: navList

        anchors.left: parent.left
        anchors.verticalCenter: parent.verticalCenter

        height: 500
        width: 300

        model: mainModel
        delegate: SideListDelegate{}
    }

    ListView {
        anchors.left: navList.right

        height: parent.height
        width: parent.width - navList.width
        model: mainModel.getSubModel(navList.currentIndex)
        delegate: MouseArea {
            height: 60
            width: 500

            Text {
                text: displayString
            }

            onClicked: mainModel.getSubModel(navList.currentIndex).constructMainNavigationModel(index)
        }
    }
}

