import QtQuick 2.1
import "pageCreator.js" as PageCreator
import CppEnums 1.0
import QtQuick.Controls 1.0

ApplicationWindow {
    id: appWindow

    Rectangle {
        id: screenContainer
        anchors.fill: parent

        FontLoader {
            id: fontAwesome
            source: "qrc:/Files/fontawesome-webfont.ttf"
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

        IconButton {
            id: aboutButton
            anchors.left: screenContainer.left
            anchors.bottom: screenContainer.bottom
            icon: "\uf05a"
            hoverText: "About"
            visible: pageStack.stackDepth == 1
            onClicked: {
                wizardContent.sourceComponent = aboutDialog
                wizardContent.show()
            }
        }

        // this is expected to be globally accessable as a means of loading wizard pages
        WizardLoader {
            id: wizardContent
        }

        Component {
            id: aboutDialog
            InfoDialog {
                id: dialog
                dialogText: "<b>EvalWriter</b>" +
                            "<br><br>Copyright 2013 Steven Hurd" +
                            "<br>All rights reserved" +
                            "<br><br>Version: " + appVersion

                Component.onCompleted:
                {
                    dialog.onCanceled.connect(wizardContent.close)
                    dialog.onCloseClicked.connect(wizardContent.close)
                }

            }
        }
    }
}
