import QtQuick 2.0

Item {
    property alias sourceComponent: pageLoader.sourceComponent

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

    Component.onCompleted: { wizardContent.visible = false }

    function show()
    {
        wizardContent.visible = true
        screenContent.enabled = false
    }

    function close()
    {
        wizardContent.visible = false
        screenContent.enabled = true
    }
}
