import QtQuick 2.0
import "stack.js" as Stack

Rectangle {
    id: wrapper

    anchors.fill: parent

    Rectangle {
        id: container
        anchors.fill: parent

        function setAsParent(item) {
            item.parent = container
        }
    }


    function push(page)
    {
        Stack.push(page)
        container.setAsParent(page)
    }

    function pop()
    {
        var item = Stack.pop()
    }
}
