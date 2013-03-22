import QtQuick 2.0
import "pageCreator.js" as PageCreator

Rectangle {
    id: wrapper
    anchors.fill: parent
    property alias model: navList.model

    ListView {
        id: navList

        anchors.left: parent.left
        anchors.verticalCenter: parent.verticalCenter

        height: 500
        width: 300

        delegate: SideListDelegate{}

        Component.onCompleted: currentIndex = 0
    }

    ListView {
        anchors.left: navList.right

        height: parent.height
        width: parent.width - navList.width
        model: { console.log(navList.currentIndex)
            return wrapper.model.getSubModel(navList.currentIndex)
        }
        delegate: MouseArea {
            height: 60
            width: 500

            Text {
                text: displayString
            }

            onClicked: {
                pageLoader.sourceComponent = PageCreator.createModelByType(wrapper.model.getSubModelType(navList.currentIndex),
                                                            wrapper.model.getSubModel(navList.currentIndex).getSubModelFromIndex(index))
            }
        }
    }
}

