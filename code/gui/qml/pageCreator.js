

function createModel(modelType, cppModel) {

}



//Creation is split into two functions due to an asynchronous wait while
//possible external files are loaded.
function loadModel(modelFile) {

    var itemComponent = Qt.createComponent("CriteriaItemRow.qml");
    if (itemComponent.status == Component.Loading)  //Depending on the content, it can be ready or error immediately
        component.statusChanged.connect(createCriteriaItemRow);
    else
        createCriteriaItemRow();
}

function createCriteriaItemRow() {
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
                                                     "color": "lightsteelblue",
                                                     "border.color": "black",
                                                     "visible": false });

        if(draggedItem === null)
        {
            console.log("Error creating object")
            return
        }

        draggedItem.Drag.active = true
        draggedItem.Drag.hotSpot.x = startingMouse.x
        draggedItem.Drag.hotSpot.y = startingMouse.y
        draggedItem.Drag.keys = "add"

    } else if (itemComponent.status == Component.Error) {
        draggedItem = null;
        console.log("error creating component");
        console.log(itemComponent.errorString());
    }
}
