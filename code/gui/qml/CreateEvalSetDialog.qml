import QtQuick 2.0

Dialog {
    id: wrapper

    property string explanationText
    property var stringList
    property int operation

    signal okClicked(int itemSelected, int operation, string name, string prefix)
    signal cancelClicked

    Component {
        id: itemChooser

        Column {
            width: 300
            spacing: 15

            Text {
                width: parent.width
                text: explanationText
                renderType: Text.NativeRendering
                wrapMode: Text.WordWrap
            }

            Rectangle {
                width: parent.width
                height: itemSelectorList.contentHeight + 10
                color: "transparent"
                CommonListView {
                    id: itemSelectorList
                    anchors.fill: parent
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
                    text: "Create"
                    onClicked: trySubmit()
                }

                TextButton {
                    id: cancelButton
                    text: "Cancel"
                    onClicked: cancelClicked()
                }
            }

            function trySubmit()
            {
                okClicked(itemSelectorList.currentIndex, wrapper.operation, "test", "test")
            }

        }
    }

    sourceComponent: itemChooser
}
