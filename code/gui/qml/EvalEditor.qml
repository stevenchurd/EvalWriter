import QtQuick 2.1
import QtQuick.Controls 1.0
import QtQuick.Layouts 1.0

Item {
    property alias model: myeval.evalModel

    SplitView {
        anchors.fill: parent
        orientation: Qt.Horizontal

        Item {
            id: leftColumn

            Layout.minimumWidth: 200
            GradingCriteriaModel{ editable: false }

            Component.onCompleted: width = settings.value("evalSplit");
        }

        Item {
            id: rightColumn
            Layout.minimumWidth: 400
            EvalModel{ id: myeval }
        }

        onResizingChanged: settings.setValue("evalSplit", leftColumn.width)
    }

    function getTitle()
    {
        return model.getEvalTitle()
    }
}
