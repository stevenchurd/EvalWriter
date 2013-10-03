import QtQuick 2.0

Item {
    id: dialogContainer

    height: parent.height
    width: pageLoader.width
    x: -400

    Loader {
        id:pageLoader
        anchors.left: parent.left
        focus: true

        onSourceChanged: {
            console.log("source component changed " + (0 - dialogContainer.width))
            dialogContainer.x = (0 - dialogContainer.width)
        }
    }

    Behavior on x {
        NumberAnimation{ duration: 200; easing.type: Easing.OutQuad }
    }

    Component.onCompleted: {
        screenOverlay.enabled = false
        x = 0 - width
    }

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

    function setSourceComponent(newDialog, properties)
    {
        pageLoader.setSource(newDialog, properties)
        pageLoader.item.canceled.connect(close)
        pageLoader.item.close.connect(close)
    }

    function setSourceComponentWithSubmit(newDialog, properties, submitAction)
    {
        setSourceComponent(newDialog, properties)
        pageLoader.item.submitted.connect(submitAction)
    }

    function setSourceComponentWithSecondarySubmit(newDialog, properties, submitAction, secondarySubmitAction)
    {
        setSourceComponentWithSubmit(newDialog, properties, submitAction)
        pageLoader.item.secondarySubmitted.connect(secondarySubmitAction)
    }
}
