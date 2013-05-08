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
                height: itemSelectorList.contentHeight + 10
                color: "transparent"
                CommonListView {
                    id: itemSelectorList
                    anchors.fill: parent
                    clip: true
                    model: stringList
                    delegate: CommonListDelegate {
                        text: modelData
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
