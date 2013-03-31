var createdComponents = []
var createdSubModels = []

function createSubModelByType(modelType, cppModel)
{
    switch(modelType)
    {
        case 1: // StudentList = 1,
        case 2: // EvaluationList = 2,
        case 3: // CourseList = 3,
        case 4: // EvalSetList = 4,
            return createSubModel(modelType, "NavigationListSubModel.qml", cppModel);

        // GradingCriteria = 5
        default:
            return createSubModel(modelType, "GradingCriteriaModel.qml", cppModel);
            break;
    }
}


function createSubModel(modelType, modelFile, cppModel) {
    var itemComponent = Qt.createComponent(modelFile);

    createdComponents.push(itemComponent)

    if (itemComponent.status === Component.Ready) {
        var newModel
        switch(modelType)
        {
            case 1: // StudentList = 1,
            case 2: // EvaluationList = 2,
            case 3: // CourseList = 3,
            case 4: // EvalSetList = 4,
                newModel = itemComponent.createObject(null, {"model": cppModel, "modelType": modelType});
                break;

            case 5: // GradingCriteria = 5
                newModel = itemComponent.createObject(null, {"editable": true});
                break;
        }
    }
    else if (itemComponent.status === Component.Error)
    {
        console.log("error creating component");
        console.log(itemComponent.errorString());
    }

    if(itemComponent === null)
        console.log("Error, created invalid component")

    createdSubModels.push(newModel)
}


function getSubModel(index)
{
    return createdSubModels[index];
}


function isListModelType(modelType)
{
    switch(modelType)
    {
        case 1: //StudentList
        case 2: //EvaluationList
        case 3: //CourseList
        case 4: //EvalSetList
            return true

        case 5: //GradingCriteria
            return false
    }
}
