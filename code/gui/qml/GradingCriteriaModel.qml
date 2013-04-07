import QtQuick 2.0

Item {
    id: wrapper

    property bool editable

    anchors.fill: parent
    anchors.margins: 5

    ListView {
        id: gradingCriteriaList

        height: parent.height
        width: parent.width - (scrollbar.width+5)
        clip: true

        model: gradingCriteriaModel
        delegate: GradingCriteriaDelegate{ editable: wrapper.editable }
        spacing: 5
    }

    Scrollbar {
        id: scrollbar
        target: gradingCriteriaList
    }
}
