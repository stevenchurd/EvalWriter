import QtQuick 2.0

Item {
    id: dialogContainer

    height: parent.height
    width: pageLoader.width
    x: -400
    state: "closed"

    states: [
        State {
            name: "showing"
            PropertyChanges { target: dialogContainer; x: 0 }
        },
        State {
            name: "closed"
            PropertyChanges { target: dialogContainer; x: 0-dialogContainer.width }
        }
    ]

    transitions: [
        Transition {
            from: "showing"
            to: "closed"
            PropertyAnimation { properties: "x"; duration: 200; easing.type: Easing.OutQuad }
        },
        Transition {
            from: "closed"
            to: "showing"
            PropertyAnimation { properties: "x"; duration: 200; easing.type: Easing.OutQuad }
        }
    ]

    Loader {
        id:pageLoader
        anchors.left: parent.left
        focus: true

        onSourceChanged: {
            dialogContainer.x = (0 - dialogContainer.width)
        }
    }

    Component.onCompleted: {
        screenOverlay.enabled = false
    }

    function show()
    {
        pageStack.enabled = false
        navBar.enabled = false
        aboutButton.enabled = false
        screenOverlay.enabled = true
        dialogContainer.state = "showing"
   }

    function close()
    {
        dialogContainer.state = "closed"
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
