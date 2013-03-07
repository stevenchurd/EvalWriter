var itemComponent = null;
var draggedItem = null;
var startingMouse;
var posnInWindow;
var copiedItem = null;

function startDrag(mouse, originalItem)
{
    posnInWindow = decorativeRect.mapToItem(screenContainer, 0, 0);
    startingMouse = { x: mouse.x, y: mouse.y }
    copiedItem = originalItem
    loadComponent();
}

//Creation is split into two functions due to an asynchronous wait while
//possible external files are loaded.

function loadComponent() {
    if (itemComponent != null) { // component has been previously loaded
        createItem();
        return;
    }

    itemComponent = Qt.createComponent("CriteriaItemRow.qml");
    if (itemComponent.status == Component.Loading)  //Depending on the content, it can be ready or error immediately
        component.statusChanged.connect(createItem);
    else
        createItem();
}

function createItem() {
    if (itemComponent.status == Component.Ready && draggedItem == null) {
        draggedItem = itemComponent.createObject(screenContainer,
                                                 {"x": posnInWindow.x,
                                                     "y": posnInWindow.y,
                                                     "z": 3,
                                                     "itemUniqueId": copiedItem.itemUniqueId,
                                                     "width": copiedItem.width,
                                                     "text": copiedItem.text,
                                                     "criteriaLevelValue": copiedItem.criteriaLevelValue,
                                                     "isSelected": false,
                                                     "opacity":.9,
                                                     "Drag.active": true,
                                                     "Drag.hotSpot.x": startingMouse.x,
                                                     "Drag.hotSpot.y": startingMouse.y,
                                                     "Drag.keys": "add"
                });

        if(draggedItem === null)
        {
            console.log("Error creating object")
        }
    } else if (itemComponent.status == Component.Error) {
        draggedItem = null;
        console.log("error creating component");
        console.log(itemComponent.errorString());
    }
}

function continueDrag(mouse)
{
    if (draggedItem == null)
        return;

    draggedItem.visible = true
    draggedItem.x = mouse.x + posnInWindow.x - startingMouse.x;
    draggedItem.y = mouse.y + posnInWindow.y - startingMouse.y;
}

function endDrag(mouse)
{
    if (draggedItem == null)
        return;

    draggedItem.Drag.drop();

    draggedItem.destroy();
    draggedItem = null;
}

