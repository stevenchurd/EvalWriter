import QtQuick 2.0

Item {
    id: wrapper

    property bool editable: false

    anchors.fill: parent

    CommonListView {
        id: gradingCriteriaList

        anchors.fill: parent
        model: gradingCriteriaModel
        delegate: GradingCriteriaDelegate{ editable: wrapper.editable }
        spacing: 5
    }


    Scrollbar {
        target: gradingCriteriaList
    }
}
