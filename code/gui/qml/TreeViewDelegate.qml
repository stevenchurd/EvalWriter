import QtQuick 2.0

Item {
    id: wrapper

    height: 50
    width: treeView.width

    MouseArea {
        anchors.fill: parent
        onClicked: wrapper.ListView.view.currentIndex = index
    }

    Rectangle {
        height: 1
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        color: "#d0d0d0"
    }

    Item {
        id: levelMarginElement

        width: (level>5?6:level)*32 + 5
        anchors.left: parent.left
    }

    Item {
        id: nodeOpenElement

        anchors.left: levelMarginElement.right
        anchors.verticalCenter: wrapper.verticalCenter
        height: 24
        state: "leafNode"

        Image {
            id: triangleOpenImage

            MouseArea {
                anchors.fill: parent
                onClicked: { (isOpened) ?
                                 gradingCriteriaModel.closeItem(index) :
                                 gradingCriteriaModel.openItem(index) }
            }
        }

        states: [
            State {
                name: "leafNode"
                when: !hasChildren
                PropertyChanges {
                    target: nodeOpenElement
                    visible: false
                    width: 0
                }
            },
            State {
                name: "openedNode"
                when: (hasChildren)&&(isOpened)
                PropertyChanges {
                    target: nodeOpenElement
                    visible: true
                    width: 32
                }

                PropertyChanges {
                    target: triangleOpenImage
                    source: "qrc:Files/arrowdown.png"
                }
            },
            State {
                name: "closedNode"
                when: (hasChildren)&&(!isOpened)
                PropertyChanges {
                    target: nodeOpenElement
                    visible: true
                    width: 32
                }

                PropertyChanges {
                    target: triangleOpenImage
                    source: "qrc:Files/arrowright.png"
                }
            }
        ]
    }

    Text {
        id: nameTextElement

        text: string
        font.pointSize: {(hasChildren) ? 20 : 12}
        verticalAlignment: "AlignVCenter"
        anchors.left: nodeOpenElement.right
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        renderType: Text.NativeRendering
    }

}
