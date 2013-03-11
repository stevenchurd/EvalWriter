import QtQuick 2.0

Flickable {
    id: flowListView

    contentWidth: width;
    contentHeight: flow.childrenRect.height

    property alias count: repeater.count
    property int currentIndex: -1
    property variant currentItem;
    property alias delegate: repeater.delegate
    property alias flow: flow.flow
    property alias model: repeater.model
    property alias displaced: flow.move
    property alias add: flow.add

    onCurrentIndexChanged: {
        currentItem = flowListView.currentIndex
    }

    Flow {
        id: flow
        width: parent.width
        spacing: 10

        Repeater {
            id: repeater

            onCountChanged: {
                if (flowListView.currentIndex === -1 && count > 0) {
                    flowListView.currentIndex = 0
                }
                if (flowListView.currentIndex >= count) {
                    flowListView.currentIndex = count - 1
                }
            }
        }
    }

    function findNearestItemIndex(x, y)
    {
        var closestIndex = -1
        var xDistFromClosest = 0xFFFF

        // first, check if the item is within the y bounds of any items
        // if it's not, only return the nearest item index if it's after all items
        for(var i = 0; i < count; i++)
        {
            var item = repeater.itemAt(i)

            // if the item is on the same y-plane, it's a candidate for a match
            if(y >= item.y && y <= (item.y + item.height))
            {
                // find out how far we are from the item
                var xDistFromCurrItem = item.x - x

                // if we're inside an item, use it
                if(x >= item.x && x <= (item.x + item.width))
                {
                    closestIndex = i
                    xDistFromClosest = 0
                }
                // if we're not inside an item, find the next item
                else if(xDistFromCurrItem > 0 && xDistFromClosest > xDistFromCurrItem)
                {
                    closestIndex = i
                    xDistFromClosest = xDistFromCurrItem
                }
            }
            else if(i == count-1 && y > item.y + item.height)
            {
                // if we're not on the same y-plane as an item, only count it
                // if we're further down than the last item
                closestIndex = count
            }
        }

        // if we don't have a valid index, it is either because we are between row
        // or because we are at the end of a row.  Handle the later case and ignore
        // the former
        if(closestIndex == -1)
        {
            for(var i = 0; i < count; i++)
            {
                var item = repeater.itemAt(i)

                if(y >= item.y && y <= (item.y + item.height))
                {
                    closestIndex = i+1;
                }
            }
        }

        return closestIndex
    }

}
