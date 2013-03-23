import QtQuick 2.0

MouseArea {
    id: wrapper
    property string myText: submodelName

    width: parent.width
    height: 62

    Text {
        text: submodelName
    }

    onClicked: {
        wrapper.ListView.view.currentIndex = index
    }
}
