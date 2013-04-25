import QtQuick 2.0

Rectangle {
    id: wrapper

    Connections {
        target: pageStack
        onPageChanged: {
            getTitleStrings()
        }
    }

    Connections {
        target: pdm
        onCourseDataChanged: getTitleStrings()
        onStudentDataChanged: getTitleStrings()
        onEvalSetDataChanged: getTitleStrings()
        onEvalDataChanged: getTitleStrings()
    }

    ListModel{
        id: titlesModel
    }

    ListView {
        height: parent.height
        width: parent.width
        anchors.verticalCenter: parent.verticalCenter
        anchors.margins: 5

        orientation: ListView.Horizontal
        interactive: false

        model: titlesModel
        delegate: NavigationBarDelegate {}
    }

    Component.onCompleted: getTitleStrings()

    function getTitleStrings()
    {
        titlesModel.clear()
        var titles = pageStack.getTitles()
        for(var i = 0; i < titles.length; i++)
        {
            titlesModel.append({"title": titles[i]})
        }
    }
}
