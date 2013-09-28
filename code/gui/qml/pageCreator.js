function createModelByType(modelType, cppModel)
{
    switch(modelType)
    {
        case 1: // StudentList = 1,
            return createModel("MainNavigationModel.qml", cppModel, "StudentNavPage");

        case 2: // EvaluationList = 2,
            return createModel("EvalEditor.qml", cppModel, "EvalEditorPage");

        case 3: // CourseList = 3,
            return createModel("MainNavigationModel.qml", cppModel, "CourseNavPage");

        case 4: // EvalSetList = 4,
            return createModel("MainNavigationModel.qml", cppModel, "EvalSetNavPage");

        // GradingCriteria = 5
        default:
            console.log("No model type: " + modelType)
            break;
    }
}


function createModel(modelFile, cppModel, typeString) {
    var itemComponent = Qt.createComponent(modelFile);

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
