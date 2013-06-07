import QtQuick 2.0

Rectangle {
    id: searchBox

    property int activeWidth
    signal textChanged(string newText)

    border.color: "#dddddd"
    state: "inactive"
    radius: 4

    Row {
        anchors.fill: parent
        IconButton {
            id: searchButton
            icon: "\uf002"
            anchors.verticalCenter: parent.verticalCenter

            onClicked: {
                searchBox.state = "active"
                filterText.focus = true
            }
        }

        TextInput {
            id: filterText
            width: parent.width - searchButton.width - clearButton.width
            anchors.verticalCenter: parent.verticalCenter
            renderType: TextInput.NativeRendering

            onFocusChanged: if(activeFocus) { selectAll() }
            onTextChanged: searchBox.textChanged(text)
        }

        IconButton {
            id: clearButton
            icon: "\uf057"
            anchors.verticalCenter: parent.verticalCenter

            onClicked: {
                filterText.remove(0, filterText.text.length)
                searchBox.state = "inactive"
            }
        }
    }

    states: [
        State {
            name: "active"
            PropertyChanges { target: filterText; visible: true }
            PropertyChanges { target: clearButton; visible: true }
            PropertyChanges { target: searchBox; width: activeWidth }
        },
        State {
            name: "inactive"
            PropertyChanges { target: filterText; visible: false }
            PropertyChanges { target: clearButton; visible: false }
            PropertyChanges { target: searchBox; width: searchButton.width }
        }
    ]

    transitions: [
        Transition { to: "active";
            NumberAnimation { target: searchBox; property: "width"; to: activeWidth; duration: 300; }
        },
        Transition { to: "inactive";
            NumberAnimation { target: searchBox; property: "width"; to: searchButton.width; duration: 100; }
        }
    ]

}

