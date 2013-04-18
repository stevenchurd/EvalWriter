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
        anchors.fill: parent

        orientation: ListView.Horizontal
        interactive: false

        model: titlesModel
        delegate: Text {
                id: titleText

                // TODO: do something if the list goes off the screen
                font.pointSize: 16
                font.family: (index === 0) ? fontAwesome.name : ""
                text: (index === 0) ? "\uf015" : " / " + title
                MouseArea {
                    anchors.fill: parent
                    onClicked: pageStack.popTo(index)
                }
            }
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
