var hoverTextItem = null

function createHoverText(mouse, text)
{
    if(hoverTextItem !== null) {
        updatePosition(mouse)
        return
    }

    var hoverComponent = Qt.createComponent("HoverText.qml")

    if(hoverComponent.status === Component.Ready && hoverComponent !== null) {
        hoverTextItem = hoverComponent.createObject(screenContainer,
                                                    {"x": mouse.x,
                                                     "y": mouse.y,
                                                     "text": text});
    }
}


function updatePosition(mouse)
{
}


function destroyHoverText()
{
    hoverTextItem.destroy()
    hoverTextItem = null
}


function createModel(modelFile, cppModel, typeString) {
    var itemComponent = Qt.createComponent(modelFile);

    createdComponents.push(itemComponent)

    if (itemComponent.status === Component.Ready) {
        var newPage = itemComponent.createObject(null, {"model": cppModel, "pageType": typeString});

    } else if (itemComponent.status === Component.Error) {
        console.log("error creating component");
        console.log(itemComponent.errorString());
    }

    if(itemComponent === null)
        console.log("Error, created invalid component")

    return newPage
}
