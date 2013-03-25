import QtQuick 2.0
import "pageCreator.js" as PageCreator
import "utilities.js" as JsUtil

Rectangle {
    id: wrapper
    anchors.fill: parent

    property var model
    property string pageType

    ListView {
        id: navList

        anchors.left: parent.left
        anchors.verticalCenter: parent.verticalCenter

        height: parent.height
        width: 300

        model: wrapper.model
        delegate: SideListDelegate{}

        onCurrentIndexChanged: subList.sourceComponent = getSubListComponent(currentIndex)
    }

    Loader {
        id: subList
        anchors.left: navList.right
        height: parent.height
        width: parent.width - navList.width
    }

    Component {
        id: mainNavSubListComponent
        ListView {
            model: wrapper.model.getSubModel(navList.currentIndex)
            delegate: MouseArea {
                height: 60
                width: 500

                Text {
                    // FIX for issue where garbage collection doesn't clean this up before new model is loaded
                    text: JsUtil.isListModelType(wrapper.model.getSubModelType(navList.currentIndex)) ? displayString : ""
                }

                onClicked: {
                    pageStack.push(PageCreator.createModelByType(wrapper.model.getSubModelType(navList.currentIndex),
                                                                 wrapper.model.getSubModel(navList.currentIndex).getSubModelFromIndex(index)))
                }
            }
        }
    }

    Component {
        id: gradingCategoriesSubListComponent
        GradingCriteriaModel { editable: true }
    }

    function getTitle()
    {
        return wrapper.model.getModelTitle()
    }


    function getSubListComponent(newIndex)
    {
        switch(wrapper.model.getSubModelType(newIndex))
        {
            case 1: //StudentList
            case 2: //EvaluationList
            case 3: //CourseList
            case 4: //EvalSetList
                return mainNavSubListComponent

            case 5: //GradingCriteria
                return gradingCategoriesSubListComponent

            default:
                console.log("Error: not a recognized sub model type: " + wrapper.model.getSubModelType(navList.currentIndex))
                break;
        }
    }
}

