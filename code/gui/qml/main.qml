import QtQuick 2.0

Rectangle {
    id: screenContainer
    width: 800
    height: 600

    Item {
        id: screenContent
        anchors.fill: parent
        GradingCriteriaModel{}
    }

    WizardLoader {
        id: wizardContent
    }

    Component {
        id: yesNo
        YesNoDialog {
            id: yesNoDialog
            dialogText: "Do you wish to continue?"

            Component.onCompleted: yesNoDialog.onCanceled.connect(wizardContent.close)

        }
    }

    Component.onCompleted: wizardContent.initialSourceComponent = yesNo

}
