import QtQuick 2.0
import "pageCreator.js" as PageCreator
import "subModelCreator.js" as SubModelCreator
import "utilities.js" as JsUtil
import CppEnums 1.0

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
        width: 200
        spacing: 5

        model: wrapper.model
        delegate: SideListDelegate{}

        highlight: Canvas {
            id: canvas
            antialiasing: true
            renderTarget: Canvas.Image

            onPaint: {
                var ctx = canvas.getContext('2d');
                ctx.save()

                ctx.fillStyle = "#555555"
                // Draw shapes
                ctx.clearRect(0,0,canvas.width, canvas.height);
                ctx.beginPath();
                ctx.moveTo(0,0)
                ctx.lineTo(0, canvas.height)
                ctx.lineTo(canvas.width*.93, canvas.height)
                ctx.lineTo(canvas.width, canvas.height/2)
                ctx.lineTo(canvas.width*.93, 0)
                ctx.lineTo(canvas.width*.93, 0)
                ctx.lineTo(0, 0)
                ctx.fill()
                ctx.restore()
            }
        }

        interactive: false

        onCurrentIndexChanged: {
            subList.children = 0
            var subModel = SubModelCreator.getSubModel(currentIndex)
            if(subModel !== undefined)
                subModel.parent = subList
        }
    }

    Rectangle {
        id: subList
        anchors.left: navList.right
        height: parent.height
        width: parent.width - navList.width
    }

    Component.onCompleted: {
        createAllSubModels()
        var subModel = SubModelCreator.getSubModel(0)
        subModel.parent = subList
    }


    function createAllSubModels()
    {
        for(var i = 0; i < model.getSubModelCount(); i++)
        {
            SubModelCreator.createSubModelByType(model.getSubModelType(i), model.getSubModel(i))
        }
    }


    function getTitle()
    {
        return wrapper.model.getModelTitle()
    }
}
