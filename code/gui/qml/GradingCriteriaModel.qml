import QtQuick 2.0

FocusScope {
    property alias interactive: gradingCriteriaList.interactive

    anchors.fill: parent

    onActiveFocusChanged: {
        if (activeFocus)
            mainView.state = ""
    }

    Item {
        id: wrapper

        anchors.fill: parent

        CommonListView {
            id: gradingCriteriaList

            anchors.fill: parent
            model: gradingCriteriaModel
            delegate: GradingCriteriaDelegate{}
            spacing: 5
        }


        Scrollbar {
            target: gradingCriteriaList
        }
    }
}
