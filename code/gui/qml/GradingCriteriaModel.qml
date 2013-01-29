import QtQuick 2.0

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
