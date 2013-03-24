import QtQuick 2.0
import "stack.js" as Stack

Rectangle {
    id: wrapper

    signal pageChanged

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
        printTitles()
        pageChanged()
    }

    function pop()
    {
        if(Stack.count() > 1)
        {
            var page = Stack.pop()
            page.parent = null
            page = Stack.top()
            container.setAsParent(page)
        }
        printTitles()
        pageChanged()
    }

    function popTo(i)
    {
        while(i < Stack.count()-1 && Stack.count() > 1)
        {
            var page = Stack.pop()
            page.parent = null
            page = Stack.top()
            container.setAsParent(page)
        }

        printTitles()
        pageChanged()
    }

    function getTitles()
    {
        var titles = []

        for(var i = 0; i < Stack.count(); i++)
        {
            var item = Stack.get(i)
            titles.push(item.getTitle())
        }
        return titles
    }

    function printTitles()
    {
        console.log("\nPageStack Titles")
        for(var i = 0; i < Stack.count(); i++)
        {
            var item = Stack.get(i)
            console.log(item.getTitle());
        }
        console.log("\n")
    }
}
