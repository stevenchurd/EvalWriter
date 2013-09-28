import QtQuick 2.1
import QtQuick.Controls 1.0

Rectangle {
    id: wrapper
    property alias stackDepth: pageContainer.depth

    signal pageChanged

    StackView {
        id: pageContainer
        height: parent.height
        width: parent.width
    }

    function push(page)
    {
        // first see if we are pushing a student or course MainNavigationPage
        if(page.pageType === "StudentNavPage")
        {
            // if it's a student, see if we can take out any lower students
            for(var i = pageContainer.depth-1; i > 0; i--)
            {
                var stackPage = pageContainer.get(i)
                if(stackPage.pageType === "StudentNavPage")
                {
                    pageContainer.removeAt(i)
                }
            }
        }

        if(page.pageType === "CourseNavPage")
        {
            // if it's a student, see if we can take out any lower students
            for(var j = pageContainer.depth-1; j > 0; j--)
            {
                var stackPage2 = pageContainer.get(j)
                if(stackPage2.pageType === "CourseNavPage")
                {
                    pageContainer.removeAt(j)
                }
            }
        }

        pageContainer.push(page)
        //printTitles()
        pageChanged()
    }

    function pop()
    {
        if(pageContainer.depth > 1)
        {
            pageContainer.pop()
        }
        //printTitles()
        pageChanged()
    }

    function popTo(i)
    {
        while(i < pageContainer.depth-1 && pageContainer.depth > 1)
        {
            var page = pageContainer.pop()
        }

        //printTitles()
        pageChanged()
    }

    function getTitles()
    {
        var titles = []

        for(var i = 0; i < pageContainer.depth; i++)
        {
            var item = pageContainer.get(i)
            titles.push(item.getTitle())
        }
        return titles
    }

    function getTopTitle()
    {
        return pageContainer.top().getTitle()
    }

    function printTitles()
    {
        console.log("\nPageStack Titles")
        for(var i = 0; i < pageContainer.depth; i++)
        {
            var item = pageContainer.get(i)
            console.log(item.getTitle());
        }
        console.log("\n")
    }
}
