function createModelByType(modelType, cppModel)
{
    switch(modelType)
    {
        case 1: // main navigation model
            return createModel("MainNavigationModel.qml", cppModel);
            break;

        case 2: // evaluation model
            return createModel("EvalEditor.qml", cppModel);
            break;

        default:
            console.log("No model type: " + modelType)
            break;
    }
}


function createModel(modelFile, cppModel) {
    var itemComponent = Qt.createComponent(modelFile);

    if (itemComponent.status === Component.Ready) {
        itemComponent.createObject(screenContainer, {"model": cppModel});

    } else if (itemComponent.status === Component.Error) {
        console.log("error creating component");
        console.log(itemComponent.errorString());
    }
    return itemComponent;
}
