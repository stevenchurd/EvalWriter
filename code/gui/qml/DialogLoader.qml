import QtQuick 2.0

Item {
    id: dialogContainer
    property alias sourceComponent: pageLoader.sourceComponent

    height: parent.height
    width: pageLoader.width
    x: -400

    Loader {
        id:pageLoader
        anchors.left: parent.left
        focus: true
    }

    Behavior on x {
        NumberAnimation{ duration: 200; easing.type: Easing.OutQuad }
    }

    Component.onCompleted: {
        screenOverlay.enabled = false
        sourceComponent = aboutDialog
        x = 0 - width
    }

    onSourceComponentChanged: x = 0 - width

    function show()
    {
        pageStack.enabled = false
        navBar.enabled = false
        aboutButton.enabled = false
        screenOverlay.enabled = true
        x = 0
   }

    function close()
    {
        x = 0-width
        pageStack.enabled = true
        navBar.enabled = true
        aboutButton.enabled = true
        screenOverlay.enabled = false
    }
}
