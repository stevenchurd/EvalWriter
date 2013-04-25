import QtQuick 2.0

Dialog {
    property string explanationText
    property var stringList

    signal okClicked(int itemSelected)
    signal cancelClicked

    Component {
        id: itemChooser

        Column {
            spacing: 15

            Text {
                text: explanationText
                renderType: Text.NativeRendering
            }

            Rectangle {
                width: parent.width
                height: 100
                CommonListView {
                    id: itemSelectorList
                    anchors.fill: parent
                    currentIndex: 0
                    model: stringList
                    delegate: Text {
                        text: modelData
                        MouseArea {
                            anchors.fill: parent
                            onClicked: itemSelectorList.currentIndex = index
                        }
                    }
                }
            }

            Row {
                spacing: 15

                TextButton {
                    id: okButton
                    text: "OK"
                    onClicked: okClicked(itemSelectorList.currentIndex)
                }

                TextButton {
                    id: cancelButton
                    text: "Cancel"
                    onClicked: cancelClicked()
                }
            }
        }
    }

    sourceComponent: itemChooser
}
