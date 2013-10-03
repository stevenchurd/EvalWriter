import QtQuick 2.0

Dialog {
    id: wrapperDialog
    property string explanationText
    property var stringList
    property var operation

    signal submitted(int operation, int itemSelected)

    Component {
        id: itemChooser

        Column {
            spacing: 15

            Connections {
                target: wrapperDialog
                onSubmitClick: { submitted(operation, itemSelectorList.currentIndex); close() }
            }

            Text {
                text: explanationText
                color: dialogTextColor
                renderType: Text.NativeRendering
            }

            Rectangle {
                height: itemSelectorList.height
                width: parent.width
                color: "transparent"

                CommonListView {
                    id: itemSelectorList
                    numElementsVisible: 12
                    width: parent.width - (scrollbar.width + 5)
                    clip: true
                    model: stringList
                    delegate: CommonListDelegate {
                        text: modelData
                    }
                }

                Scrollbar {
                    id: scrollbar
                    target: itemSelectorList
                }
            }
        }
    }

    sourceComponent: itemChooser
}
