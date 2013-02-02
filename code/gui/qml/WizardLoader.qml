import QtQuick 2.0

Item {
    property alias initialSourceComponent: pageLoader.sourceComponent
    property alias initialSource: pageLoader.source

    anchors.fill: parent

    Rectangle {
        anchors.fill: parent
        color: "lightgray"
        opacity: .5
    }


    Loader {
        id:pageLoader
        anchors.centerIn: parent
    }

    Component.onCompleted: { screenContent.enabled = false }

    function close()
    {
        wizardContent.visible = false
        screenContent.enabled = true
    }
}
