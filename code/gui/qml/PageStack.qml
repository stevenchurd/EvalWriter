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
        // first see if we are pushing a student or course MainNavigationPage
        if(page.pageType === "StudentNavPage")
        {
            // if it's a student, see if we can take out any lower students
            for(var i = Stack.count()-1; i > 0; i--)
            {
                var stackPage = Stack.get(i)
                if(stackPage.pageType === "StudentNavPage")
                {
                    Stack.removeAt(i)
                }
            }
        }

        if(page.pageType === "CourseNavPage")
        {
            // if it's a student, see if we can take out any lower students
            for(var j = Stack.count()-1; j > 0; j--)
            {
                var stackPage2 = Stack.get(j)
                if(stackPage2.pageType === "CourseNavPage")
                {
                    Stack.removeAt(j)
                }
            }
        }

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
