import QtQuick 2.0

Item {
    id: wrapper

    anchors.fill: parent

    CommonListView {
        id: gradingCriteriaList

        width: parent.width
        height: parent.height

        model: gradingCriteriaModel
        delegate: GradingCriteriaDelegate{
            id: gcDelegate
        }
    }

    Scrollbar {
        target: gradingCriteriaList
    }
}
