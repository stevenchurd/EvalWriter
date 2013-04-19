var hoverTextItem = null

function createHoverText(mouse, text, parent)
{
    var posnInWindow = parent.mapToItem(screenContainer, 0, 0);

    if(hoverTextItem !== null) {
        updatePosition(mouse, posnInWindow)
        return
    }

    var hoverComponent = Qt.createComponent("HoverText.qml")

    if(hoverComponent.status === Component.Ready && hoverComponent !== null) {
        hoverTextItem = hoverComponent.createObject(screenContainer,
                                                     {"text": text});
        updatePosition(mouse, posnInWindow)
    }
}


function updatePosition(mouse, posnInWindow)
{
    if(hoverTextItem.visible === false)
    {
        hoverTextItem.x = posnInWindow.x + mouse.x
        hoverTextItem.y = posnInWindow.y + mouse.y + 20

        if(hoverTextItem.x + hoverTextItem.width > screenContainer.width)
        {
            hoverTextItem.x -= hoverTextItem.width
        }

        if(hoverTextItem.y + hoverTextItem.height > screenContainer.height)
        {
            hoverTextItem.y -= hoverTextItem.height
        }
    }
}


function destroyHoverText()
{
    if(hoverTextItem !== null)
    {
        hoverTextItem.destroy()
        hoverTextItem = null
    }
}

