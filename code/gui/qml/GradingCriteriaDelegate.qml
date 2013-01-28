import QtQuick 2.0

CommonListView {
    width: parent.width
    height: 30 * count
    model: gradingCriteriaModel.criteriaItemModel(index)
    header: Text{
        id: gcRow
        text: gradingCriteriaString
    }
    delegate: Text{
            id: itemRow
            text: criteriaString
        }
}
