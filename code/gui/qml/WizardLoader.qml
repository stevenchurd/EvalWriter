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
        focus: true
   }

    Component.onCompleted: { wizardContent.visible = false }

    function show()
    {
        wizardContent.visible = true
        pageStack.enabled = false
        navBar.enabled = false
        aboutButton.enabled = false
    }

    function close()
    {
        wizardContent.sourceComponent = emptyComponent
        wizardContent.visible = false
        pageStack.enabled = true
        navBar.enabled = true
        aboutButton.enabled = true
    }

    Component {
        id: emptyComponent
        Rectangle {
            color: "transparent"

            visible: false
            height:1
            width:1
        }
    }
}
