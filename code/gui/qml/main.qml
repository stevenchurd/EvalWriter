import QtQuick 2.0
import "pageCreator.js" as PageCreator

Rectangle {
    id: screenContainer
    width: 800
    height: 600

    PageStack {
        id: pageStack
        anchors.fill: parent

        Component.onCompleted: {
            pageStack.push(PageCreator.createModel("MainNavigationModel.qml", mainModel))
        }
    }

    // this is expected to be globally accessable as a means of loading wizard pages
    WizardLoader {
        id: wizardContent
    }
}
