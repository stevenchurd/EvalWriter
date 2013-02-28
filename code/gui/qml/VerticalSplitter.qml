//Reusable VerticalSplitter.qml
import QtQuick 2.0

Rectangle{
    id: splitterRect

    anchors.left: firstRect.right
    anchors.right: firstRect.right
    anchors.rightMargin: -10

    width: 10
    height: :w.height
    clip: true

    property QtObject firstRect;
    property QtObject secondRect;

    property int maximizedRect : -1;

    function moveSplitterTo(x)
    {
        if(x > 0 && x < :w.width - splitterRect.width)
        {
            firstRect.width = x;
            secondRect.width = :w.width - firstRect.width - splitterRect.width;
        }
    }

    function maximizeRect(x)
    {
        firstRect.width = x===0 ? :w.width - splitterRect.width : 0
        secondRect.width = x===0 ? 0 : :w.width - splitterRect.width
    }

    Component.onCompleted: {
        firstRect.height = height;
        firstRect.width = (firstRect.parent.width - width)/2;
        firstRect.anchors.left = firstRect.parent.left;

        secondRect.anchors.left = splitterRect.right;
        secondRect.anchors.right = secondRect.parent.right;
        secondRect.height = height;
    }

    onXChanged: {
        moveSplitterTo(splitterRect.x);
    }

    BorderImage {
        id: splitterBorder
        anchors.fill: parent
        source: "qrc:Files/arrowdown.png"
    }

    Image{
        id: arrows
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        source: "qrc:Files/arrowdown.png"
    }

    MouseArea {
        anchors.fill: parent
        drag.axis: Drag.XAxis
        drag.target: splitterRect

        onClicked: {
            maximizedRect = maximizedRect == 1 ? 0 : 1;
            maximizeRect(maximizedRect);
        }
    }
}
