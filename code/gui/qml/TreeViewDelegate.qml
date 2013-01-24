import QtQuick 2.0

Item {
    id: wrapper

    width: parent.width
    height: loaderElement.height

    MouseArea {
        anchors.fill: parent
        onClicked: wrapper.ListView.view.currentIndex = index
    }

    // this is the line between the items
//    Rectangle {
//        height: 1
//        border.width: (isGradingCriteria) ? 1 : 0
//        anchors.top: parent.top
//        anchors.left: parent.left
//        anchors.right: parent.right
//        color: "#d0d0d0"
//    }

    Row {
        Item {
            id: nodeOpenElement

            anchors.verticalCenter: parent.verticalCenter
            height: 24
            width: {(isGradingCriteria) ? 32 : 50}

            Image {
                id: triangleOpenImage
                anchors.verticalCenter: parent.verticalCenter
                anchors.horizontalCenter: parent.horizontalCenter

                MouseArea {
                    anchors.fill: parent
                    onClicked: { (isOpened) ?
                                     gradingCriteriaModel.closeItem(index) :
                                     gradingCriteriaModel.openItem(index) }
                }
            }

            states: [
                State {
                    name: "openedNode"
                    when: (hasChildren)&&(isOpened)

                    PropertyChanges {
                        target: triangleOpenImage
                        source: "qrc:Files/arrowdown.png"
                    }
                },
                State {
                    name: "closedNode"
                    when: (hasChildren)&&(!isOpened)

                    PropertyChanges {
                        target: triangleOpenImage
                        source: "qrc:Files/arrowright.png"
                    }
                }
            ]
        }

        Loader {
            id: loaderElement
            width: wrapper.width - nodeOpenElement.width

            sourceComponent: textElement

        }
    }

    Component {
        id: textElement
        Text {
            id: nameTextElement

            text:{(isGradingCriteria) ? (string + " (" + numChildren + ")") : (string)}
            font.pointSize:{(isGradingCriteria) ? 16: 10}
            wrapMode: Text.WordWrap
            verticalAlignment: "AlignVCenter"
            renderType: Text.NativeRendering

//            Rectangle {
//                width: parent.width
//                height: parent.height
//                color: "transparent"
//                border.color: "lightgray"
//            }

            Image {
                id: addImage
                source: "qrc:Files/arrowright.png"
                anchors.right: parent.right
                visible: (wrapper.ListView.view.currentIndex === index)
            }
        }
   }
}
