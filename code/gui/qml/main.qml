import QtQuick 2.0
import "pageCreator.js" as PageCreator
import CppEnums 1.0

Rectangle {
    id: screenContainer
    width: 800
    height: 600

    FontLoader {
        id: fontAwesome
        source: "../../../../../FortAwesome-Font-Awesome-v3.0.2-0-g13d5dd3/FortAwesome-Font-Awesome-13d5dd3/font/fontawesome-webfont.ttf"
    }

    NavigationBar {
        id: navBar
        height: 50
        width: parent.width
    }

    PageStack {
        id: pageStack
        anchors.top: navBar.bottom
        height: screenContainer.height - navBar.height
        width: parent.width

        Component.onCompleted: {
            pageStack.push(PageCreator.createModel("MainNavigationModel.qml", mainModel))
        }
    }

    // this is expected to be globally accessable as a means of loading wizard pages
    WizardLoader {
        id: wizardContent
    }
}
