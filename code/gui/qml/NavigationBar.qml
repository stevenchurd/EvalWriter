import QtQuick 2.0

Rectangle {
    id: wrapper

    Connections {
        target: pageStack
        onPageChanged: {
            getTitleStrings()
        }
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
                font.pointSize: 15
                text: " / " + title
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
