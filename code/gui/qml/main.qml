import QtQuick 2.0
import "pageCreator.js" as PageCreator

Rectangle {
    id: screenContainer
    width: 800
    height: 600

    Item {
        id: screenContent
        anchors.fill: parent
        Loader {
            id: pageLoader
        }
//        EvalEditor{}
//        GradingCriteriaModel{
//            editable: true
//        }
    }

    // this is expected to be globally accessable as a means of loading wizard pages
    WizardLoader {
        id: wizardContent
    }

    Component.onCompleted: pageLoader.sourceComponent = PageCreator.createModel("MainNavigationModel.qml", mainModel)
}
