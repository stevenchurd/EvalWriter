import QtQuick 2.0

Rectangle {
    id: window

    anchors.fill: parent

    FocusScope {
        id: mainView

        width: parent.width; height: parent.height
        focus: true

        Item {
            id: screenContent
            anchors.fill: parent
            GradingCriteriaModel{}
            focus: true
        }

        Rectangle {
            id: shade
            anchors.fill: parent
            color: "black"
            opacity: 0
        }

        states: State {
            name: "showListViews"
            PropertyChanges { target: screenContent; y: -160 }
            PropertyChanges { target: screenContent; y: 160 }
        }

        transitions: Transition {
            NumberAnimation { properties: "y"; duration: 600; easing.type: Easing.OutQuint }
        }
    }

    Image {
        source: "qrc:Files/arrow.png"
        rotation: 90
        anchors.verticalCenter: parent.verticalCenter

        MouseArea {
            anchors.fill: parent; anchors.margins: -10
            onClicked: contextMenu.focus = true
        }
    }

    ContextMenu { id: contextMenu; x: -265; width: 260; height: parent.height }

    states: State {
        name: "contextMenuOpen"
        when: !mainView.activeFocus
        PropertyChanges { target: contextMenu; x: 0; open: true }
        PropertyChanges { target: mainView; x: 130 }
        PropertyChanges { target: shade; opacity: 0.25 }
    }

    transitions: Transition {
        NumberAnimation { properties: "x,opacity"; duration: 600; easing.type: Easing.OutQuint }
    }
}
